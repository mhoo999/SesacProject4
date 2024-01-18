// zombie must die


#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"
#include "ZombieAnim.h"


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

void AZombieBase_KJY::Damage()
{
	auto Anim = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
	Anim->PlayDamageAnim();
	
	CurrentHp--;
	UE_LOG(LogTemp, Warning, TEXT("Hp--"));
	if(	CurrentHp <= 0)
	{
		Die();
	}
	//Me->GetCharacterMovement()->MaxWalkSpeed = 0;
}

void AZombieBase_KJY::Die()
{
	auto Anim = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
	Anim->PlayDieAnim();

	Destroy();

}

