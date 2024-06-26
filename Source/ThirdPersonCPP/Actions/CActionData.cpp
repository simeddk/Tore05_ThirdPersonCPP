#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform Transform;

	if (EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, Transform, InOwnerCharacter);
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(MakeActorLable(InOwnerCharacter, "Equipment"));
		Equipment->FinishSpawning(Transform);
	}
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
