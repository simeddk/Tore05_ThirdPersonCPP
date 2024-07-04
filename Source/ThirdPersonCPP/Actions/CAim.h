#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CAim.generated.h"

class ACharacter;
class USpringArmComponent;
class UCameraComponent;
class UCurveFloat;
class ACHUD;

UCLASS()
class THIRDPERSONCPP_API UCAim : public UObject
{
	GENERATED_BODY()

public:
	UCAim();

	void BeginPlay(ACharacter* InOwnerCharacter);
	void Tick(float DeltaTime);

	void On();
	void Off();

	FORCEINLINE bool CanAim() { return SpringArmComp != nullptr && CameraComp != nullptr; }
	FORCEINLINE bool IsZooming() { return bZooming; }

private:
	UFUNCTION()
	void OnProgress(float Output);

private:
	ACharacter* OwnerCharacter;
	USpringArmComponent* SpringArmComp;
	UCameraComponent* CameraComp;

	bool bZooming;
	UCurveFloat* Curve;
	FTimeline Timeline;

	ACHUD* HUD;
};
