#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "CAction.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, UCAction** OutAction)
{
	FTransform Transform;

	ACAttachment* Attachment = nullptr;
	if (AttachmentClass)
	{	
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, Transform, InOwnerCharacter);
		Attachment->SetActorLabel(MakeActorLable(InOwnerCharacter, "Attachment"));
		Attachment->FinishSpawning(Transform);
	}

	ACEquipment* Equipment = nullptr;
	if (EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, Transform, InOwnerCharacter);
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(MakeActorLable(InOwnerCharacter, "Equipment"));
		Equipment->FinishSpawning(Transform);

		if (Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnequip);
		}
	}

	ACDoAction* DoAction = nullptr;
	if (DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, Transform, InOwnerCharacter);
		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(MakeActorLable(InOwnerCharacter, "DoAction"));
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoAction->FinishSpawning(Transform);
		
		if (Equipment)
		{
			DoAction->SetEquipped(Equipment->IsEquipped());
		}

		if (Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentEndOverlap);
		}
	}

	*OutAction = NewObject<UCAction>();
	(*OutAction)->Attachment = Attachment;
	(*OutAction)->Equipment = Equipment;
	(*OutAction)->DoAction = DoAction;
	(*OutAction)->EquipmentColor = EquipmentColor;
}

FString UCActionData::MakeActorLable(ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString Label;
	Label.Append(InOwnerCharacter->GetActorLabel());
	Label.Append("_");
	Label.Append(InMiddleName);
	Label.Append("_");
	Label.Append(GetName().Replace(TEXT("DA_"), TEXT("")));

	return Label;
}
