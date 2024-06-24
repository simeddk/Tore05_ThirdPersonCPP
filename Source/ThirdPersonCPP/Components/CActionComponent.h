#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, MagicBall, Warp, Whirlwind, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsUnaremdMode() { return Type == EActionType::Unaremd; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsFistMode() { return Type == EActionType::Fist; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsOneHandMode() { return Type == EActionType::OneHand; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsMagicBallMode() { return Type == EActionType::MagicBall; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsWarpMode() { return Type == EActionType::Warp; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsWhirlwindMode() { return Type == EActionType::Whirlwind; }

public:
	void SetUnaremdMode();
	void SetFistMode();
	void SetOneHandMode();
	void SetTwoHandMode();
	void SetMagicBallMode();
	void SetWarpMode();
	void SetWhirlwindMode();

private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FActionTypeChanged OnActionTypeChanged;

private:
	EActionType Type;
};
