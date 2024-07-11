#include "CAttributeComponent.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	WalkSpeeds[(int32)EWalkSpeedType::Sneak] = 200;
	WalkSpeeds[(int32)EWalkSpeedType::Walk] = 400;
	WalkSpeeds[(int32)EWalkSpeedType::Sprint] = 600;

	MaxHealth = 100.f;
	
	bCanMove = true;
}


void UCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UCAttributeComponent::IncreaseHealth(float InAmount)
{
	CurrentHealth += InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UCAttributeComponent::DecreaseHealth(float InAmount)
{
	CurrentHealth -= InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UCAttributeComponent::SetMove()
{
	bCanMove = true;
}

void UCAttributeComponent::SetStop()
{
	bCanMove = false;
}

void UCAttributeComponent::SetWalkSpeed(EWalkSpeedType InWalkSpeed)
{
	UCharacterMovementComponent* MovementComp = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	CheckNull(MovementComp);

	MovementComp->MaxWalkSpeed = WalkSpeeds[(int32)InWalkSpeed];
}
