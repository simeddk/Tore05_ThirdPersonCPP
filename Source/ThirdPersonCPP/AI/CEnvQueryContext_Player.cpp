#include "CEnvQueryContext_Player.h"
#include "Global.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/Character.h"
#include "Components/CBehaviorComponent.h"
#include "Characters/CPlayer.h"

void UCEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	
	ACharacter* Querior = Cast<ACharacter>(QueryInstance.Owner.Get());
	if (Querior)
	{
		UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(Querior->GetController());
		if (BehaviorComp)
		{
			ACPlayer* Player = BehaviorComp->GetPlayerKey();
			if (Player)
			{
				UEnvQueryItemType_Actor::SetContextHelper(ContextData, Player);
				return;
			}
		}
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Querior);
}