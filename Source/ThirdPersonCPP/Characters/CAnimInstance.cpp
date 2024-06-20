#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* Charater = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Charater);

	Speed = Charater->GetVelocity().Size2D();
	Direction = CalculateDirection(Charater->GetVelocity(), Charater->GetControlRotation());
}