#include "CPatrolComponent.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "AI/CPatrolPath.h"

UCPatrolComponent::UCPatrolComponent()
{

}


void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UCPatrolComponent::GetMoveTo(FVector& OutLoation)
{
	OutLoation = GetOwner()->GetActorLocation();
	CheckFalseResult(IsPathValid(), false);

	OutLoation = PatrolPath->GetSplineComp()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	return true;
}

void UCPatrolComponent::UpdateNextIndex()
{
	CheckNull(PatrolPath);

	int32 Count = PatrolPath->GetSplineComp()->GetNumberOfSplinePoints();

	//Reverse
	if (bReverse)
	{
		if (Index > 0)
		{
			Index--;
			return;
		}

		if (PatrolPath->GetSplineComp()->IsClosedLoop())
		{
			Index = Count - 1;
			return;
		}

		Index = 1;
		bReverse = false;

		return;
	}

	//Forward
	if (Index < Count - 1)
	{
		Index++;
		return;
	}

	if (PatrolPath->GetSplineComp()->IsClosedLoop())
	{
		Index = 0;
		return;
	}

	Index = Count - 2;
	bReverse = true;
}