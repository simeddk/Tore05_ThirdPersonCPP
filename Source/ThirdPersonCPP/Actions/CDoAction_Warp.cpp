#include "CDoAction_Warp.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"
#include "CAttachment.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Child : OwnerCharacter->Children)
	{
		if (Child->IsA<ACAttachment>() && Child->GetActorLabel().Contains("Warp"))
		{
			PreviewMeshComp = CHelpers::GetComponent<USkeletalMeshComponent>(Child);
			break;
		}
	}
	
}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PreviewMeshComp->SetVisibility(false);

	CheckFalse(*bEquipped);

	FVector CurLoc;
	FRotator CurRot;
	if (GetCursorLocationAndRotation(CurLoc, CurRot))
	{
		PreviewMeshComp->SetVisibility(true);
		PreviewMeshComp->SetWorldLocation(CurLoc);
	}

}

void ACDoAction_Warp::DoAction()
{
	Super::DoAction();

	CheckFalse(StateComp->IsIdleMode());

	FRotator Temp;
	CheckFalse(GetCursorLocationAndRotation(Location, Temp));

	StateComp->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();

	SetPreviewMeshColor(FLinearColor(20, 0, 0));
}

void ACDoAction_Warp::Begin_DoAction()
{
	Super::Begin_DoAction();

	FTransform Trasnform = Datas[0].EffectTransform;
	Trasnform.AddToTranslation(OwnerCharacter->GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld() ,Datas[0].Effect, Trasnform);
}

void ACDoAction_Warp::End_DoAction()
{
	Super::End_DoAction();

	Location.Z += OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	OwnerCharacter->SetActorLocation(Location);

	StateComp->SetIdleMode();
	AttributeComp->SetMove();

	SetPreviewMeshColor(FLinearColor(0, 20, 20));
}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(ObjectTypeQuery1);

	FHitResult Hit;
	if (PC->GetHitResultUnderCursorForObjects(ObjectTypes, true, Hit))
	{
		OutLocation = Hit.Location;
		OutRotation = Hit.ImpactNormal.Rotation();

		return true;
	}

	return false;
}


void ACDoAction_Warp::SetPreviewMeshColor(FLinearColor InColor)
{
	FVector FromColor = FVector(InColor.R, InColor.G, InColor.B);
	PreviewMeshComp->SetVectorParameterValueOnMaterials("Emissive", FromColor);
}