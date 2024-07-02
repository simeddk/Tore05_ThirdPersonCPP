#include "CEnemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Widgets/CEnemyNameWidget.h"
#include "Widgets/CEnemyHealthWidget.h"

ACEnemy::ACEnemy()
{
	//Property Settings
	LaunchValue = 25.f;

	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &NameWidgetComp, "NameWidgetComp", GetMesh());
	CHelpers::CreateSceneComponent(this, &HealthWidgetComp, "HealthWidgetComp", GetMesh());

	//Create Actor Component
	CHelpers::CreateActorComponent(this, &ActionComp, "ActionComp");
	CHelpers::CreateActorComponent(this, &MontagesComp, "MontagesComp");
	CHelpers::CreateActorComponent(this, &AttributeComp, "AttributeComp");
	CHelpers::CreateActorComponent(this, &StateComp, "StateComp");

	//Component Settings
	//-> MeshComp
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Character/Mesh/SK_Mannequin");
	GetMesh()->SetSkeletalMesh(MeshAsset);

	TSubclassOf<UAnimInstance> AnimInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&AnimInstanceClass, "/Game/Enemies/ABP_CEnemy");
	GetMesh()->SetAnimInstanceClass(AnimInstanceClass);

	//-> Movmement
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	//-> Widget
	TSubclassOf<UCEnemyNameWidget> NameWidgetAsset;
	CHelpers::GetClass(&NameWidgetAsset, "/Game/Widgets/WB_EnemyName");
	NameWidgetComp->SetWidgetClass(NameWidgetAsset);
	NameWidgetComp->SetRelativeLocation(FVector(0, 0, 240));
	NameWidgetComp->SetDrawSize(FVector2D(240, 30));
	NameWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UCEnemyHealthWidget> HealthWidgetAsset;
	CHelpers::GetClass(&HealthWidgetAsset, "/Game/Widgets/WB_EnemyHealth");
	HealthWidgetComp->SetWidgetClass(HealthWidgetAsset);
	HealthWidgetComp->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidgetComp->SetDrawSize(FVector2D(120, 15));
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy::BeginPlay()
{
	//Create Dynamic Material
	UMaterialInstanceConstant* BodyMaterialAsset;
	UMaterialInstanceConstant* LogoMaterialAsset;

	CHelpers::GetAssetDynamic(&BodyMaterialAsset, "/Game/Character/Materials/MI_UE4Man_Body");
	CHelpers::GetAssetDynamic(&LogoMaterialAsset, "/Game/Character/Materials/M_UE4Man_ChestLogo");

	BodyMaterial = UMaterialInstanceDynamic::Create(BodyMaterialAsset, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(LogoMaterialAsset, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	StateComp->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	Super::BeginPlay();

	ActionComp->SetUnarmedMode();

	NameWidgetComp->InitWidget();
	UCEnemyNameWidget* NameWidgetInstance = Cast<UCEnemyNameWidget>(NameWidgetComp->GetUserWidgetObject());
	if (NameWidgetInstance)
	{
		NameWidgetInstance->SetName(GetController()->GetName(), GetName());
	}

	HealthWidgetComp->InitWidget();
	UCEnemyHealthWidget* HealthWidgetInstance = Cast<UCEnemyHealthWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (HealthWidgetInstance)
	{
		HealthWidgetInstance->ApplyHealth(AttributeComp->GetCurrentHealth(), AttributeComp->GetMaxHealth());
	}
}

void ACEnemy::ChangeBodyColor(FLinearColor InColor)
{
	CheckTrue(StateComp->IsDeadMode());

	if (StateComp->IsHittedMode())
	{
		LogoMaterial->SetScalarParameterValue("bHitted", 1.f);
		LogoMaterial->SetVectorParameterValue("LogoEmissive", InColor);

		return;
	}

	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
 	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	DamageInstigator = EventInstigator;
	
	AttributeComp->DecreaseHealth(Damage);

	if (AttributeComp->GetCurrentHealth() <= 0.f)
	{
		StateComp->SetDeadMode();
		return 0.f;
	}

	StateComp->SetHittedMode();

	return DamageValue;
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Hitted:
		{
			Hitted();
		}
		break;

		case EStateType::Dead:
		{
			Dead();
		}
		break;
	}
}

void ACEnemy::Hitted()
{
	//Apply Health Widget
	UCEnemyHealthWidget* HealthWidgetInstance = Cast<UCEnemyHealthWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (HealthWidgetInstance)
	{
		HealthWidgetInstance->ApplyHealth(AttributeComp->GetCurrentHealth(), AttributeComp->GetMaxHealth());
	}

	//Play Hitted Montage
	MontagesComp->PlayHitted();

	//Look At Attack
	FVector Start = GetActorLocation();
	FVector Target = DamageInstigator->GetPawn()->GetActorLocation();
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
	SetActorRotation(FRotator(0, Rotation.Yaw, 0));

	//Hit Back
	FVector Direction = Target - Start;
	Direction.Normalize();
	LaunchCharacter(-Direction * DamageValue * LaunchValue, true, false);

	//Set Hitted Logo Color
	ChangeBodyColor(FLinearColor(40, 0, 0));
	UKismetSystemLibrary::K2_SetTimer(this, "RestoreLogoColor", 0.5f, false);
}

void ACEnemy::Dead()
{
	//Hidden Widgets
	NameWidgetComp->SetVisibility(false);
	HealthWidgetComp->SetVisibility(false);

	//Ragdoll
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	//Off All Attachemnt Collisions
	ActionComp->OffAllCollsions();

	//Todo. DissovleMAT -> Dynamic -> Timeline : Amount
}

void ACEnemy::RestoreLogoColor()
{
	LogoMaterial->SetScalarParameterValue("bHitted", 0.f);
}