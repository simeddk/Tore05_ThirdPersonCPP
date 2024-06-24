#include "CActionComponent.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCActionComponent::SetUnaremdMode()
{
}

void UCActionComponent::SetFistMode()
{
}

void UCActionComponent::SetOneHandMode()
{
}

void UCActionComponent::SetTwoHandMode()
{
}

void UCActionComponent::SetMagicBallMode()
{
}

void UCActionComponent::SetWarpMode()
{
}

void UCActionComponent::SetWhirlwindMode()
{
}

void UCActionComponent::SetMode(EActionType InNewType)
{
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	//Todo. 위 코드 이어서 치기
	EActionType Prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
	{
		OnActionTypeChanged.Broadcast(Prev, InNewType);
	}
}
