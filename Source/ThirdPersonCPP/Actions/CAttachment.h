#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

class ACharacter;
class UShapeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, ACharacter*, InAttacker, AActor*, InCauser, ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlap, ACharacter*, InAttacker, AActor*, InCauser, ACharacter*, InOtherCharacter);

UCLASS()
class THIRDPERSONCPP_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUnequip();

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
public:
	void OnCollision();
	void OffCollision();

public:
	UPROPERTY(BlueprintAssignable)
	FAttachmentBeginOverlap OnAttachmentBeginOverlap;

	UPROPERTY(BlueprintAssignable)
	FAttachmentEndOverlap OnAttachmentEndOverlap;

protected:
	UFUNCTION(BlueprintCallable)
	void ActorAttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable)
	void ComponentAttachTo(USceneComponent* InComp, FName InSocketName);

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacter* OwnerCharacter;

private:
	TArray<UShapeComponent*> Collisions;
};
