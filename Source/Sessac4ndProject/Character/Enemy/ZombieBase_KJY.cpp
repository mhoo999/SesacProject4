// zombie must die


#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"


// 기본적으로 목적지(지켜야 하는곳)를 향해 감
// 플레이어가 일정 범위 내에 들어오면 플레이어 향해 이동, 공격(매우 근접)
AZombieBase_KJY::AZombieBase_KJY()
{
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UZombieFSM>(TEXT("FSM"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AZombieBase_KJY::BeginPlay()
{
	Super::BeginPlay();
}

void AZombieBase_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
                                                           