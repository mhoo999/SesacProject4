// zombie must die


#include "SMGPlayer_YMH.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerBaseComp.h"


ASMGPlayer_YMH::ASMGPlayer_YMH()
{
	weaponeGrade = 1;
	bulletCount = 30;
	fireSpeed = 1.0f;
}

void ASMGPlayer_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void ASMGPlayer_YMH::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
