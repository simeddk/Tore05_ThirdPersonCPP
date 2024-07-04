#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset(&CrossHairTexture, "/Game/Game/T_Crosshair");
}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	StateComp = CHelpers::GetComponent<UCStateComponent>(PlayerCharacter);

	StateTypeAsUEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStateType"));
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	if (StateComp && StateTypeAsUEnum)
	{
		FString StateTypeString = StateTypeAsUEnum->GetNameStringByValue((int64)StateComp->GetType());
		DrawText("CurrentState : " + StateTypeString, FLinearColor::Red, 10.f, Canvas->ClipY - 30.f);
	}


	CheckFalse(bVisibleAim);
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D ImageHalfSize(CrossHairTexture->GetSizeX() * 0.5f, CrossHairTexture->GetSizeY() * 0.5f);
	Center -= ImageHalfSize;

	FCanvasTileItem Item(Center, CrossHairTexture->Resource, FLinearColor::White);
	Item.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(Item);
}

void ACHUD::VisibleAim()
{
	bVisibleAim = true;
}

void ACHUD::InvisibleAim()
{
	bVisibleAim = false;
}
