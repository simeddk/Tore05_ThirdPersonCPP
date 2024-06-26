// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CCharacterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class THIRDPERSONCPP_API ICCharacterInterface
{
	GENERATED_BODY()

public:
	virtual void ChangeBodyColor(FLinearColor InColor) = 0;
};
