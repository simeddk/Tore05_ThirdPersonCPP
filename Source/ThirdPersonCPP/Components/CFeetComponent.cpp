#include "CFeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UCFeetComponent::UCFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LeftFootSocketName = "Foot_L";
	RightFootSocketName = "Foot_R";

	DrawDebugType = EDrawDebugTrace::ForOneFrame;

	Additional = 55.f;
	FootHeight = 7.5f;
	InterpSpeed = 16.f;
}


void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}


void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float LeftDistance;
	FRotator LeftRotation;
	Trace(LeftFootSocketName, LeftDistance, LeftRotation);

	float RightDistance;
	FRotator RightRotation;
	Trace(RightFootSocketName, RightDistance, RightRotation);

	float Floating = FMath::Min(LeftDistance, RightDistance);

	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, Floating, DeltaTime, InterpSpeed);

	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, (LeftDistance - Floating), DeltaTime, InterpSpeed);
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(RightDistance - Floating), DeltaTime, InterpSpeed);
}

void UCFeetComponent::Trace(FName InSocketName, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.f;

	FVector SocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InSocketName);
	FVector Start = FVector(SocketLocation.X, SocketLocation.Y, OwnerCharacter->GetActorLocation().Z);
	
	float TraceZ = Start.Z - CapsuleHalfHeight - Additional;
	FVector End = FVector(SocketLocation.X, SocketLocation.Y, TraceZ);

	TArray<AActor*> Ignores;
	Ignores.Add(OwnerCharacter);

	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		Ignores,
		DrawDebugType,
		Hit,
		true
	);

	CheckFalse(Hit.bBlockingHit);

	float Length = (Hit.ImpactPoint - Hit.TraceEnd).Size();
	OutDistance = FootHeight + Length - Additional;

	//Todo. Rotate Foot
	FVector ImpactNormal = Hit.ImpactNormal;
	OutRotation = ImpactNormal.Rotation();
}

