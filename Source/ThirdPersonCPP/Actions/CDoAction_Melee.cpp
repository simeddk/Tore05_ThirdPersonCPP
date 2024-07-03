#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);
	if (bCanCombo)
	{
		bCanCombo = false;
		bSuccessCombo = true;

		return;
	}

	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bSuccessCombo);
	bSuccessCombo = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage();
	ComboCount = 0;

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_Melee::EnableCombo()
{
	bCanCombo = true;
}

void ACDoAction_Melee::DisableCombo()
{
	bCanCombo = false;
}

void ACDoAction_Melee::ClearHittedCharacters()
{
	HittedCharacters.Empty();
}

void ACDoAction_Melee::RestoreGlobalTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	//Blocking Multiple Hit
	int32 NuumberOfHittedCharacters = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);
	CheckFalse(NuumberOfHittedCharacters < HittedCharacters.Num());

	//HitStop
	float HitStop = Datas[ComboCount].HitStop;
	if (FMath::IsNearlyZero(HitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.02f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreGlobalTimeDilation", HitStop * 0.02f, false);
	}

	TSubclassOf<UCameraShake> ShakeClass = Datas[ComboCount].ShakeClass;
	if (ShakeClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
		}
	}

	//Hit Particle
	UParticleSystem* HitEffect = Datas[ComboCount].Effect;
	if (HitEffect)
	{
		FTransform Trasform = Datas[ComboCount].EffectTransform;
		Trasform.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Trasform);
	}

	//Take Damage
	FDamageEvent DamageEvent;
	InOtherCharacter->TakeDamage(Datas[ComboCount].Power, DamageEvent, InAttacker->GetController(), InCauser);
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}