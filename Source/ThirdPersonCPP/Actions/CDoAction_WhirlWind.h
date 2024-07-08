#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_WhirlWind.generated.h"

class UParticleSystemComponent;
class UBoxComponent;
class ACharacter;

UCLASS()
class THIRDPERSONCPP_API ACDoAction_WhirlWind : public ACDoAction
{
	GENERATED_BODY()

public:
	ACDoAction_WhirlWind();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Abort() override;

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) override;

private:
	UFUNCTION()
	void TickDamage();

	UFUNCTION()
	void Finish();

private:
	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float DamageToTime;

	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float ActiveTime;

	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float AroundSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float Radius;

	UPROPERTY(VisibleInstanceOnly)
	UParticleSystemComponent* AttachedParticleComp;

private:
	UBoxComponent* BoxComp;
	bool bActivating;

	TArray<ACharacter*> HittedCharacters;
	float CurrentYaw;
};
