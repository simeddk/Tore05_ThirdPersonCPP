#include "CBehaviorComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{

}


void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCBehaviorComponent::SetBlackboardComp(UBlackboardComponent* InComp)
{
	BlackboardComp = InComp;
	//Todo.. 나머지는 내일..
}

bool UCBehaviorComponent::IsWaitMode()
{
	return false;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return false;
}

bool UCBehaviorComponent::IsActionMode()
{
	return false;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return false;
}

bool UCBehaviorComponent::IsHittedMode()
{
	return false;
}

bool UCBehaviorComponent::IsEscapeMode()
{
	return false;
}

void UCBehaviorComponent::SetWaitMode()
{
}

void UCBehaviorComponent::SetApproachMode()
{
}

void UCBehaviorComponent::SetActionMode()
{
}

void UCBehaviorComponent::SetPatrolMode()
{
}

void UCBehaviorComponent::SetHittedMode()
{
}

void UCBehaviorComponent::SetEscapeMode()
{
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
}

EBehaviorType UCBehaviorComponent::GetType()
{
	return EBehaviorType();
}
