#include "COptionComponent.h"

UCOptionComponent::UCOptionComponent()
{
	MouseXRate = 45.f;
	MouseYRate = 45.f;

	ZoomSpeed = 1000.f;
	ZoomRange = FVector2D(100.f, 500.f);
}


void UCOptionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}