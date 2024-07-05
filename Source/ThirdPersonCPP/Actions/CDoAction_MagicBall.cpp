#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CAttributeComponent.h"
#include "Components/CStateComponent.h"
#include "CAim.h"
#include "CProjectile.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	ActionComp->OnActionTypeChanged.AddDynamic(this, &ACDoAction_MagicBall::AbortByActionTypeChanged);
}

void ACDoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_MagicBall::DoAction()
{
	Super::DoAction();

	if (Aim->CanAim())
	{
		CheckFalse(Aim->IsZooming());
	}

	CheckFalse(Datas.Num() > 0);
	CheckFalse(StateComp->IsIdleMode());

	StateComp->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);

	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_MagicBall::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckNull(Datas[0].ProjectileClass);
	
	FVector CamLoc;
	FRotator CamRot;
	OwnerCharacter->GetController()->GetPlayerViewPoint(CamLoc, CamRot);

	FVector HandLocation = OwnerCharacter->GetMesh()->GetSocketLocation("hand_r");

	FVector SpawnLoctaion = CamLoc + CamRot.Vector() * ((HandLocation - CamLoc) | CamRot.Vector());

	FTransform Tranform;
	Tranform.SetLocation(SpawnLoctaion);
	Tranform.SetRotation(FQuat(CamRot));

	ACProjectile* ProjectileIntance = GetWorld()->SpawnActorDeferred<ACProjectile>(Datas[0].ProjectileClass, Tranform, OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	ProjectileIntance->OnProjectileBeginOverlap.AddDynamic(this, &ACDoAction_MagicBall::OnProjectileBeginOverlap);
	ProjectileIntance->FinishSpawning(Tranform);
}

void ACDoAction_MagicBall::End_DoAction()
{
	Super::End_DoAction();
	
	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_MagicBall::Begin_SubAction()
{
	Aim->On();
}

void ACDoAction_MagicBall::End_SubAction()
{
	Aim->Off();
}

void ACDoAction_MagicBall::OnProjectileBeginOverlap(FHitResult InHitResult)
{
	if (Datas[0].Effect)
	{
		FTransform EffectTransform = Datas[0].EffectTransform;
		EffectTransform.AddToTranslation(InHitResult.ImpactPoint);
		EffectTransform.SetRotation(FQuat(InHitResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Datas[0].Effect, EffectTransform);
	}

	TSubclassOf<UCameraShake> ShakeClass = Datas[0].ShakeClass;
	if (ShakeClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
		}
	}

	FDamageEvent DamageEvent;
	InHitResult.GetActor()->TakeDamage(Datas[0].Power, DamageEvent, OwnerCharacter->GetController(), this);
}

void ACDoAction_MagicBall::AbortByActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->CanAim());
	CheckFalse(Aim->IsZooming());

	Aim->Off();
}
