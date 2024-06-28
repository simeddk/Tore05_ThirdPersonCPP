#include "CEnemyHealthWidget.h"
#include "Components/ProgressBar.h"

void UCEnemyHealthWidget::ApplyHealth_Implementation(float InCurrentHealth, float InMaxHealth)
{
	HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
}
