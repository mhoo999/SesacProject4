// zombie must die


#include "PlayerController/PlayerController_YMH.h"

#include "NetworkMessage.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "UI/MainUI_YMH.h"

void APlayerController_YMH::BeginPlay()
{
	Super::BeginPlay();

	InitUIWidget();
}

void APlayerController_YMH::InitUIWidget()
{
	if (mainUIWidget)
	{
		mainUI = Cast<UMainUI_YMH>(CreateWidget(GetWorld(), mainUIWidget));
		mainUI->AddToViewport();
		mainUI->ShowPointer();
		mainUI->SelectSlot(0);

		mainUI->RemoveAllAmmo();
		/*auto player = Cast<APlayerBase_YMH>(GetOwner());
		if (Player)
		{
			for (int i = 0; i < player->MaxBulletCount; ++i)
			{
				mainUI->AddBullet();
			}
		}*/
	}
}