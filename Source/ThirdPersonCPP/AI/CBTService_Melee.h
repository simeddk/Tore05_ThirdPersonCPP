#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Melee.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCBTService_Melee : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_Melee();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
