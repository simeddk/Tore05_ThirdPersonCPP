#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

class UCActionData;
class UCAction;

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
	void DoAction();

	void DoSubAction(bool bBegin);

	void OffAllCollsions();

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE UCAction* GetCurrentActionData() { return Datas[(int32)Type]; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UCActionData* GetCurrentActionDataAsset() { return DataAssets[(int32)Type]; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }

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
	UFUNCTION(BlueprintCallable)
	void SetUnarmedMode();

	UFUNCTION(BlueprintCallable)
	void SetFistMode();

	UFUNCTION(BlueprintCallable)
	void SetOneHandMode();

	UFUNCTION(BlueprintCallable)
	void SetTwoHandMode();

	UFUNCTION(BlueprintCallable)
	void SetMagicBallMode();
	
	UFUNCTION(BlueprintCallable)
	void SetWarpMode();

	UFUNCTION(BlueprintCallable)
	void SetWhirlwindMode();

private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FActionTypeChanged OnActionTypeChanged;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
	UCActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;

	UPROPERTY()
	UCAction* Datas[(int32)EActionType::Max];

};
