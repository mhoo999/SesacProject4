// zombie must die


#include "SMGPlayer_YMH.h"
#include "PlayerFireComp_YMH.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"

ASMGPlayer_YMH::ASMGPlayer_YMH()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SMG(TEXT("/Script/Engine.SkeletalMesh'/Game/SimpleApocalypse/Meshes/Weapons/RiggedWeapons/SK_Wep_AssaultRifle_02.SK_Wep_AssaultRifle_02'"));
	if (SMG.Succeeded()) Weapon->SetSkeletalMeshAsset(SMG.Object);
	
	maxHelth = 10.0f;
	currentHealth = maxHelth;
	FireComp->attackSpeed = 2.0f;
	FireComp->Damage = 10.0f;
	FireComp->attackDistance = 4000;
	FireComp->weaponeGrade = 1;
	FireComp->MaxBulletCount = 30.0f;
	FireComp->bulletCount = 30.0f;
	FireComp->reloadBulletCount = 30.0f;
	FireComp->MaxRecoilValue = -0.7f;
	FireComp->MinRecoilValue = -1.0f;
	FireComp->crosshairRecoilValue = 2.0;
}

void ASMGPlayer_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void ASMGPlayer_YMH::OnRep_Owner()
{
	Super::OnRep_Owner();

	FireComp->attackSpeed = 2.0f;
	FireComp->Damage = 10.0f;
	FireComp->attackDistance = 4000;
	FireComp->weaponeGrade = 1;
	FireComp->MaxBulletCount = 30.0f;
	FireComp->bulletCount = 30.0f;
	FireComp->reloadBulletCount = 30.0f;
	FireComp->MaxRecoilValue = -0.7f;
	FireComp->MinRecoilValue = -1.0f;
	FireComp->crosshairRecoilValue = 2.0;
}

void ASMGPlayer_YMH::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASMGPlayer_YMH::SetCrosshair()
{
	Super::SetCrosshair();
	
	/*auto pc = Cast<APlayerController_YMH>(Controller);
	if (pc)
	{
		pc->mainUI->ShowPointer();
	}*/
}
