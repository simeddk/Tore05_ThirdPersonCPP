#include "CAnimNotifyState_Combo.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CAction.h"
#include "Actions/CDoAction_Melee.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCAction* ActionData = ActionComp->GetCurrentActionData();
	CheckNull(ActionData);

	ACDoAction_Melee* DoAction_Melee = Cast<ACDoAction_Melee>(ActionData->GetDoAction());
	CheckNull(DoAction_Melee);

	DoAction_Melee->EnableCombo();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCAction* ActionData = ActionComp->GetCurrentActionData();
	CheckNull(ActionData);

	ACDoAction_Melee* DoAction_Melee = Cast<ACDoAction_Melee>(ActionData->GetDoAction());
	CheckNull(DoAction_Melee);

	DoAction_Melee->DisableCombo();
}
