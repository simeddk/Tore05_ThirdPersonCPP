#include "CEnemyNameWidget.h"
#include "Components/TextBlock.h"

void UCEnemyNameWidget::SetName(FString InControllerName, FString InPawnName)
{
	ControllerName->SetText(FText::FromString(InControllerName));
	PawnName->SetText(FText::FromString(InPawnName));
}
