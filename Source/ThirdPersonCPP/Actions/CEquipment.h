#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CEquipment.generated.h"

class ACharacter;
class UCStateComponent;
class UCAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipmentDelegate);

UCLASS()
class THIRDPERSONCPP_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE const bool* IsEquipped() { return &bEquipped; } //실시간성 보장

	void SetData(const FEquipmentData& InData);
	void SetColor(const FLinearColor& InColor);

public:
	UFUNCTION(BlueprintNativeEvent)
	void Equip();

	UFUNCTION(BlueprintNativeEvent)
	void Begin_Equip();

	UFUNCTION(BlueprintNativeEvent)
	void End_Equip();

	UFUNCTION(BlueprintNativeEvent)
	void Unequip();

public:
	UPROPERTY(BlueprintAssignable)
	FEquipmentDelegate OnEquipmentDelegate;

	UPROPERTY(BlueprintAssignable)
	FUnequipmentDelegate OnUnequipmentDelegate;

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly)
	UCAttributeComponent* AttributeComp;

private:
	FEquipmentData Data;
	FLinearColor Color;

	bool bEquipped;
};
