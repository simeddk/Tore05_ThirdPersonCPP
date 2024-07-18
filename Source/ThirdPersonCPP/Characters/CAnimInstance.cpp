#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CheckNull(TryGetPawnOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(TryGetPawnOwner());
	CheckNull(ActionComp);

	ActionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* Charater = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Charater);

	Speed = Charater->GetVelocity().Size2D();
	Direction = CalculateDirection(Charater->GetVelocity(), Charater->GetControlRotation());

	UCFeetComponent* FeetComp = CHelpers::GetComponent<UCFeetComponent>(Charater);
	CheckNull(FeetComp);

	FeetData = FeetComp->GetData();
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}