#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CAction.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction_Melee.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCAction* ActionData = ActionComp->GetCurrentActionData();
	CheckNull(ActionData);

	ACAttachment* Attachment = ActionData->GetAttachment();
	CheckNull(Attachment);

	Attachment->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCAction* ActionData = ActionComp->GetCurrentActionData();
	CheckNull(ActionData);

	ACAttachment* Attachment = ActionData->GetAttachment();
	CheckNull(Attachment);

	Attachment->OffCollision();
	
	ACDoAction_Melee* DoAction_Melee = Cast<ACDoAction_Melee>(ActionData->GetDoAction());
	CheckNull(DoAction_Melee);
	
	DoAction_Melee->ClearHittedCharacters();
}

