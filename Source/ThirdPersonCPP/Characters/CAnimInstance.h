#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CActionComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "BlendSpace")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "BlendSpace")
	float Direction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ActionComponent")
	EActionType ActionType;

};
