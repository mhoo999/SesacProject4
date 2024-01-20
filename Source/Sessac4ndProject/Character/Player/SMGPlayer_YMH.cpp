// zombie must die


#include "SMGPlayer_YMH.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerBaseComp_YMH.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"


ASMGPlayer_YMH::ASMGPlayer_YMH()
{
	maxHelth = 10.0f;
	currentHealth = maxHelth;
	attackSpeed = 2.0f;
	Damage = 10.0f;
	attackDistance = 4000;
	weaponeGrade = 1;
	MaxBulletCount = SMGBulletCount;
	bulletCount = SMGBulletCount;
	reloadBulletCount = SMGBulletCount;
	MaxRecoilValue = -0.7f;
	MinRecoilValue = -1.0f;
	crosshairRecoilValue = 2.0;
}

void ASMGPlayer_YMH::BeginPlay()
{
	Super::BeginPlay();

}

void ASMGPlayer_YMH::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
