#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	GetComponents<UShapeComponent>(Collisions);
	for (const auto& Collision : Collisions)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
		Collision->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);
	}

	OffCollision();

	Super::BeginPlay();
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor->GetClass() == OwnerCharacter->GetClass());

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	CheckNull(OtherCharacter);

	if (OnAttachmentBeginOverlap.IsBound())
	{
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, OtherCharacter);
	}
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	CheckNull(OtherCharacter);

	if (OnAttachmentEndOverlap.IsBound())
	{
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, OtherCharacter);
	}
}

void ACAttachment::OnCollision()
{
	for (const auto& Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACAttachment::OffCollision()
{
	for (const auto& Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACAttachment::ActorAttachTo(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACAttachment::ComponentAttachTo(USceneComponent* InComp, FName InSocketName)
{
	InComp->AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

