#include "CAnimNotify_Rolled.h"
#include "Global.h"
#include "Characters/CPlayer.h"

FString UCAnimNotify_Rolled::GetNotifyName_Implementation() const
{
	return "Rolled";
}

void UCAnimNotify_Rolled::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());
	
	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(Player);

	Player->End_Roll();
}