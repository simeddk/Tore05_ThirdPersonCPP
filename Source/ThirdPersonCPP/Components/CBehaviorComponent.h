#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

class UBlackboardComponent;

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, Escape
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetBlackboardComp(UBlackboardComponent* InComp);

public:
	UFUNCTION(BlueprintPure)
	bool IsWaitMode();

	UFUNCTION(BlueprintPure)
	bool IsApproachMode();

	UFUNCTION(BlueprintPure)
	bool IsActionMode();

	UFUNCTION(BlueprintPure)
	bool IsPatrolMode();

	UFUNCTION(BlueprintPure)
	bool IsHittedMode();

	UFUNCTION(BlueprintPure)
	bool IsEscapeMode();

public:
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetEscapeMode();

private:
	void ChangeType(EBehaviorType InNewType);
	EBehaviorType GetType();

private:
	UBlackboardComponent* BlackboardComp;
};
