// zombie must die


#include "Character/Player/ShotgunPlayer_YMH.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"

AShotgunPlayer_YMH::AShotgunPlayer_YMH()
{
	maxHelth = 10.0f;
	currentHealth = maxHelth;
	attackSpeed = 5.0f;
	Damage = 50.0f;
	attackDistance = 1500;
	weaponeGrade = 1;
	MaxBulletCount = shotgunBulletCount;
	bulletCount = shotgunBulletCount;
	reloadBulletCount = 1;
	MaxRecoilValue = -1.0;
	MinRecoilValue = -1.5;
	crosshairRecoilValue = 3.0f;

}

void AShotgunPlayer_YMH::BeginPlay()
{
	Super::BeginPlay();

	if (playerController->mainUI)
	{
		playerController->mainUI->ShowCrosshair(true);
	}
}

void AShotgunPlayer_YMH::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
