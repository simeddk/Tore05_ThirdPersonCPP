#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UCStateComponent;

UCLASS()
class THIRDPERSONCPP_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	void EnableSelectActionWidget();
	void DisableSelectActionWidget();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ActionWidgetClass;

	UPROPERTY()
	UUserWidget* ActionWidget;

	UPROPERTY()
	UCStateComponent* StateComp;
};
