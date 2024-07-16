#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CActionComponent.h"
#include "CBTTaskNode_ChangeAction.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCBTTaskNode_ChangeAction : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_ChangeAction();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	EActionType Type;
};
