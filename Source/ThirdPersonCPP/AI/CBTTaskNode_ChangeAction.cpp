#include "CBTTaskNode_ChangeAction.h"
#include "Global.h"
#include "AIController.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_ChangeAction::UCBTTaskNode_ChangeAction()
{
	NodeName = "ChangeAction";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_ChangeAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	APawn* Pawn = AIC->GetPawn();
	CheckNullResult(Pawn, EBTNodeResult::Failed);

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(Pawn);
	
	if (Type == EActionType::Warp && !ActionComp->IsWarpMode())
	{
		ActionComp->SetWarpMode();
	}
	else if (Type == EActionType::MagicBall && !ActionComp->IsMagicBallMode())
	{
		ActionComp->SetMagicBallMode();
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_ChangeAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);

	APawn* Pawn = AIC->GetPawn();
	CheckNull(Pawn);

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(Pawn);

	if (StateComp->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}