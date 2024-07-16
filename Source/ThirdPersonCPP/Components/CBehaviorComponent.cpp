#include "CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CPlayer.h"

UCBehaviorComponent::UCBehaviorComponent()
{
	BehaviorKey = "BehaviorKey";
	PlayerKey = "PlayerKey";
	LocationKey = "LocationKey";
}


void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCBehaviorComponent::SetBlackboardComp(UBlackboardComponent* InComp)
{
	BlackboardComp = InComp;
}

bool UCBehaviorComponent::IsWaitMode()
{
	return GetType() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return GetType() == EBehaviorType::Approach;
}

bool UCBehaviorComponent::IsActionMode()
{
	return GetType() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UCBehaviorComponent::IsHittedMode()
{
	return GetType() == EBehaviorType::Hitted;
}

bool UCBehaviorComponent::IsEscapeMode()
{
	return GetType() == EBehaviorType::Escape;
}

void UCBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

void UCBehaviorComponent::SetEscapeMode()
{
	ChangeType(EBehaviorType::Escape);
}

ACPlayer* UCBehaviorComponent::GetPlayerKey()
{
	return Cast<ACPlayer>(BlackboardComp->GetValueAsObject(PlayerKey));
}

FVector UCBehaviorComponent::GetLocationKey()
{
	return BlackboardComp->GetValueAsVector(LocationKey);
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
	BlackboardComp->SetValueAsEnum(BehaviorKey, (uint8)InNewType);
}

EBehaviorType UCBehaviorComponent::GetType()
{
	return (EBehaviorType)BlackboardComp->GetValueAsEnum(BehaviorKey);
}
