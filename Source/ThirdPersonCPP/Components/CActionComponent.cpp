#include "CActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "Actions/CAttachment.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (DataAssets[i])
		{
			DataAssets[i]->BeginPlay(OwnerCharacter);
		}
	}
}

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetDoAction())
	{
		ACDoAction* DoAction = DataAssets[(int32)Type]->GetDoAction();
		DoAction->DoAction();
	}
}

void UCActionComponent::DoSubAction(bool bBegin)
{
	CheckTrue(IsUnarmedMode());

	if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetDoAction())
	{
		ACDoAction* DoAction = DataAssets[(int32)Type]->GetDoAction();

		bBegin ? DoAction->Begin_SubAction() : DoAction->End_SubAction();
	}
}

void UCActionComponent::OffAllCollsions()
{
	for (const auto& DataAsset : DataAssets)
	{
		if (DataAsset && DataAsset->GetAttachment())
		{
			DataAsset->GetAttachment()->OffCollision();
		}
	}

}

void UCActionComponent::SetUnarmedMode()
{
	if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetEquipment())
	{
		DataAssets[(int32)Type]->GetEquipment()->Unequip();
	}

	if (DataAssets[(int32)EActionType::Unarmed] && DataAssets[(int32)EActionType::Unarmed]->GetEquipment())
	{
		DataAssets[(int32)EActionType::Unarmed]->GetEquipment()->Equip();
	}

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetWhirlwindMode()
{
	SetMode(EActionType::Whirlwind);
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	if (Type == InNewType)
	{
		SetUnarmedMode();
		return;
	}

	else if (IsUnarmedMode() == false)
	{
		if (DataAssets[(int32)Type] && DataAssets[(int32)Type]->GetEquipment())
			DataAssets[(int32)Type]->GetEquipment()->Unequip();
	}

	if (DataAssets[(int32)InNewType] && DataAssets[(int32)InNewType]->GetEquipment())
		DataAssets[(int32)InNewType]->GetEquipment()->Equip();


	ChangeType(InNewType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType Prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
	{
		OnActionTypeChanged.Broadcast(Prev, InNewType);
	}
}
