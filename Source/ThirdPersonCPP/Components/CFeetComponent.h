#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CFeetComponent.generated.h"

class ACharacter;

USTRUCT(BlueprintType)
struct FFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector LeftDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector RightDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector PelvisDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FRotator RightRotation;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCFeetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCFeetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE FFeetData GetData() { return Data; }

private:
	void Trace(FName InSocketName, float& OutDistance, FRotator& OutRotation);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
	FName LeftFootSocketName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
	FName RightFootSocketName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
	float Additional;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
	float FootHeight;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
	float InterpSpeed;

private:
	FFeetData Data;

	ACharacter* OwnerCharacter;
	float CapsuleHalfHeight;
};
