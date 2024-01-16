// zombie must die


#include "SMGPlayer_YMH.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerBaseComp_YMH.h"


ASMGPlayer_YMH::ASMGPlayer_YMH()
{
	/*weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	weapon->SetupAttachment(GetMesh());
	weapon->GetAttachSocketName(FName("WeaponSocket"));*/

	maxHelth = 10.0f;
	currentHealth = maxHelth;
	attackSpeed = 2.0f;
	Damage = 10.0f;
	attackDistance = 1000;
	weaponeGrade = 1;
	bulletCount = SMGBulletCount;
	recoilValue = 10.0;
}

void ASMGPlayer_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void ASMGPlayer_YMH::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
