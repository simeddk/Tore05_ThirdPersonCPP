#include "CBTService_Wizard.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"

UCBTService_Wizard::UCBTService_Wizard()
{
	NodeName = "Root_Wizard";
}

void UCBTService_Wizard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);

	UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);

	ACEnemy_AI* EnemyPawn = Cast<ACEnemy_AI>(AIC->GetPawn());
	CheckNull(EnemyPawn);

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);

	//Is Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();
		return;
	}

	ACPlayer* Player = BehaviorComp->GetPlayerKey();
	
	//Not Detected Player
	if (Player == nullptr)
	{
		BehaviorComp->SetWaitMode();
		AIC->ClearFocus(EAIFocusPriority::Gameplay);

		return;
	}

	AIC->SetFocus(Player);

	float Distance = EnemyPawn->GetDistanceTo(Player);

	if (Distance < AIC->GetBehaviorRange())
	{
		BehaviorComp->SetEscapeMode();
		return;
	}

	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetActionMode();
	}
}