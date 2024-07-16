#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPatrolPath.generated.h"

class USplineComponent;
class UTextRenderComponent;

UCLASS()
class THIRDPERSONCPP_API ACPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPatrolPath();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE USplineComponent* GetSplineComp() { return SplineComp; }

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly)
	USplineComponent* SplineComp;

	UPROPERTY(VisibleDefaultsOnly)
	UTextRenderComponent* TextRenderComp;

	UPROPERTY(EditInstanceOnly)
	bool bClosedLoop;
};
