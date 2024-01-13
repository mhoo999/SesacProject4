// zombie must die


#include "PlayerController/PlayerController_YMH.h"

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
		mainUI->ShowCrosshair(true);
	}
}
