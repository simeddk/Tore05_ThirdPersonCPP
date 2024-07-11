#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPatrolComponent.generated.h"

class ACPatrolPath;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPatrolComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsPathValid() { return PatrolPath != nullptr; }

	bool GetMoveTo(FVector& OutLoation);
	void UpdateNextIndex();

private:
	UPROPERTY(EditInstanceOnly, Category = "AI")
	ACPatrolPath* PatrolPath;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	int32 Index;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bReverse;
};
