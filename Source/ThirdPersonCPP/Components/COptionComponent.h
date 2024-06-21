#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCOptionComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetMouseXRate() { return MouseXRate; }
	FORCEINLINE float GetMouseYRate() { return MouseYRate; }
	
	FORCEINLINE float GetZoomSpeed() { return ZoomSpeed; }
	FORCEINLINE float GetZoomMin() { return ZoomRange.X; }
	FORCEINLINE float GetZoomMax() { return ZoomRange.Y; }

private:
	UPROPERTY(EditAnywhere, Category = "Mouse")
	float MouseXRate;

	UPROPERTY(EditAnywhere, Category = "Mouse")
	float MouseYRate;

	UPROPERTY(EditAnywhere, Category = "Mouse")
	float ZoomSpeed;

	//X is min rate, Y is max rate
	UPROPERTY(EditAnywhere, Category = "Mouse")
	FVector2D ZoomRange;
		
};
