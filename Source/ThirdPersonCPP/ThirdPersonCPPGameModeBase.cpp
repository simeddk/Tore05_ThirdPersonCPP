#include "ThirdPersonCPPGameModeBase.h"
#include "Global.h"

AThirdPersonCPPGameModeBase::AThirdPersonCPPGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
}

