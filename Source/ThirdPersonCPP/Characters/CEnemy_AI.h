#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

class UBehaviorTree;

UCLASS()
class THIRDPERSONCPP_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
};
