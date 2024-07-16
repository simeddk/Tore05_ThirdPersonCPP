#include "CPlayerController.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "Components/CStateComponent.h"

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StateComp = CHelpers::GetComponent<UCStateComponent>(InPawn);
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectAction", IE_Pressed, this, &ACPlayerController::EnableSelectActionWidget);
	InputComponent->BindAction("SelectAction", IE_Released, this, &ACPlayerController::DisableSelectActionWidget);
}

void ACPlayerController::EnableSelectActionWidget()
{
	ensure(ActionWidgetClass);

	if (StateComp)
	{
		CheckFalse(StateComp->IsIdleMode());
	}

	if (ActionWidget == nullptr)
	{
		ActionWidget = CreateWidget<UUserWidget>(this, ActionWidgetClass);
	}

	if (ActionWidget)
	{
		ActionWidget->AddToViewport();

		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());

		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f);
	}
}

void ACPlayerController::DisableSelectActionWidget()
{
	if (ActionWidget && ActionWidget->IsInViewport())
	{
		ActionWidget->RemoveFromParent();
		ActionWidget = nullptr;

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());

		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	}
}
