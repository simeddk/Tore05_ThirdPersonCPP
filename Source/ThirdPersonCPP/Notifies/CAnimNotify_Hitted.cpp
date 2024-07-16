#include "CAnimNotify_Hitted.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"

FString UCAnimNotify_Hitted::GetNotifyName_Implementation() const
{
	return "Hitted";
}

void UCAnimNotify_Hitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(StateComp);

	StateComp->SetIdleMode();
	
	UCAttributeComponent* AttributeComp = CHelpers::GetComponent<UCAttributeComponent>(MeshComp->GetOwner());
	CheckNull(AttributeComp);
	
	AttributeComp->SetMove();
}