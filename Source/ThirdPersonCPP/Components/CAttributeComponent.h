#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAttributeComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedType : uint8
{
	Sneak, Walk, Sprint, Max
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THIRDPERSONCPP_API UCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCAttributeComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE float GetSneakSpeed() { return WalkSpeeds[(int32)EWalkSpeedType::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeeds[(int32)EWalkSpeedType::Walk]; }
	FORCEINLINE float GetSprintSpeed() { return WalkSpeeds[(int32)EWalkSpeedType::Sprint]; }

	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

	void SetMove();
	void SetStop();

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float WalkSpeeds[(int32)EWalkSpeedType::Max];

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxHealth;

private:
	bool bCanMove;
	float CurrentHealth;
};
