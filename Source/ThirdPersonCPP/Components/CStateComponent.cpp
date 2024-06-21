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
		//Todo. 설명필요!!(컴파일 안함)
		EStateType Prev = Type;
		Type = InNewType;

		OnStateTypeChanged.Broadcast(Prev,InNewType);
	}
}

