// zombie must die


#include "PlayerController/PlayerController_YMH.h"

#include "NetworkMessage.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Character/Player/PlayerFireComp_YMH.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "UI/MainUI_YMH.h"

void APlayerController_YMH::BeginPlay()
{
	Super::BeginPlay();
	
	InitUIWidget();
}

void APlayerController_YMH::InitUIWidget()
{
	if (IsLocalController() && mainUIWidget)
	{
		if (mainUI == nullptr)
		{
			mainUI = Cast<UMainUI_YMH>(CreateWidget(GetWorld(), mainUIWidget));
			mainUI->AddToViewport();
			mainUI->SelectSlot(0);
		}

		auto* player = Cast<APlayerBase_YMH>(GetPawn());
		if (player)
		{
			mainUI->MaxBullet->SetText(FText::AsNumber(player->FireComp->MaxBulletCount));
			mainUI->CurrentBullet->SetText(FText::AsNumber(player->FireComp->MaxBulletCount));
		}
	}
}