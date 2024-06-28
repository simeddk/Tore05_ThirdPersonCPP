#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CEnemyNameWidget.generated.h"

class UTextBlock;

UCLASS()
class THIRDPERSONCPP_API UCEnemyNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetName(FString InControllerName, FString InPawnName);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ControllerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PawnName;
};
