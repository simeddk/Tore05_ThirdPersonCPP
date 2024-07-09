#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"

class ACEquipment;
class ACAttachment;
class ACDoAction;

UCLASS()
class THIRDPERSONCPP_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	friend class UCActionData;

public:
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE ACDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }
	
private:
	ACEquipment* Equipment;
	ACAttachment* Attachment;
	ACDoAction* DoAction;
	FLinearColor EquipmentColor;
};
