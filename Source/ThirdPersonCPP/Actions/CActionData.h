#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class ACEquipment;
class ACharacter;

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditDefaultsOnly)
	float PlayRate = 1.f;

	UPROPERTY(EditDefaultsOnly)
	FName StartSection;

	UPROPERTY(EditDefaultsOnly)
	bool bCanMove = true;

	UPROPERTY(EditDefaultsOnly)
	bool bLookForward = true;
};

UCLASS()
class THIRDPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(ACharacter* InOwnerCharacter);

private:
	FString MakeActorLable(ACharacter* InOwnerCharacter, FString InMiddleName);

public:
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }

public:
	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	FLinearColor EquipmentColor;

private:
	ACEquipment* Equipment;
	
};
