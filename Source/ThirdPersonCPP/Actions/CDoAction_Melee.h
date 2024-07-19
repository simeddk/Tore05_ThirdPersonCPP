#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"

class ACharacter;

UCLASS()
class THIRDPERSONCPP_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Abort() override;

public:
	void EnableCombo();
	void DisableCombo();
	void ClearHittedCharacters();

private:
	UFUNCTION()
	void RestoreGlobalTimeDilation();
	
private:
	int32 ComboCount;
	bool bCanCombo;
	bool bSuccessCombo;

	TArray<ACharacter*> HittedCharacters;
};
