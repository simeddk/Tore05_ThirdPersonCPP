#include "CStateComponent.h"

UCStateComponent::UCStateComponent()
{

}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void UCStateComponent::SetBackstepMode()
{
	ChangeType(EStateType::Backstep);
}

void UCStateComponent::ChangeType(EStateType InNewType)
{
	if (OnStateTypeChanged.IsBound())
	{
		EStateType Prev = Type;
		Type = InNewType;

		OnStateTypeChanged.Broadcast(Prev, InNewType);
	}
}

