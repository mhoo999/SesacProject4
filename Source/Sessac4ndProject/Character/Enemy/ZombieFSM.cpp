// zombie must die


#include "ZombieFSM.h"
#include "DestinationActor_KJY.h"
#include "ZombieBase_KJY.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UZombieFSM::UZombieFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UZombieFSM::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ADestinationActor_KJY::StaticClass());
	Target = Cast<ADestinationActor_KJY>(actor);
	Me = Cast<AZombieBase_KJY>(GetOwner());
	
}


// Called every frame
void UZombieFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	switch (mState)
	{
	case EZombieState::Move:
		MoveState();
		break;
	case EZombieState::Attack:
		AttackState();
		break;
	case EZombieState::Damage:
		DamageState();
		break;
	case EZombieState::Die:
		DieState();
		break;
	}
}

void UZombieFSM::MoveState()
{
	FVector TargetDir = Target->GetActorLocation() - Me->GetActorLocation();
	FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();

	// 목적지 향해 가다가
	Me->AddMovementInput(TargetDir.GetSafeNormal());
	
	// 플레이어가 일정 거리 내에 있으면 플레이어에게 이동
	if (PlayerDir.Size()<MovetoPlayerRange)
	{
		Me->AddMovementInput(PlayerDir.GetSafeNormal());

		// 플레이어와 가까워지면 플레이어 공격
		if (PlayerDir.Size()<AttackRange)
		{
			mState = EZombieState::Attack;
		}
	}
}

void UZombieFSM::AttackState()
{
	// 일정 시간마다 공격
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > AttackTime)
	{
		// 플레이어 공격 에니메이션
		// 플레이어 체력 닳음
		CurrentTime = 0;
	}

	FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();
	if (PlayerDir.Size()>AttackRange)
	{
		mState = EZombieState::Move;
	}
}

void UZombieFSM::DamageState()
{
}

void UZombieFSM::DieState()
{
}

