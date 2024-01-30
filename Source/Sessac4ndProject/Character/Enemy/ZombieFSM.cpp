// zombie must die


#include "ZombieFSM.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "ZombieAnim.h"
#include "Actor/DestinationActor_KJY.h"
#include "ZombieBase_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

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

	auto TargetActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADestinationActor_KJY::StaticClass());
	Target = Cast<ADestinationActor_KJY>(TargetActor);
	// auto Playeractor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerBase_YMH::StaticClass());
	GetWorld()->GetTimerManager().SetTimer(ZombieFSM_Handle, FTimerDelegate::CreateLambda([&]
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerBase_YMH::StaticClass(), Players);
	}), 3, false);
	// Player = Cast<APlayerBase_YMH>(Playeractor);

	// ----- Zombie -----
	Me = Cast<AZombieBase_KJY>(GetOwner());
	Anim = Cast<UZombieAnim>(Me->GetMesh()->GetAnimInstance());
	ai = Cast<AAIController>(Me->GetController());

	if (GetOwner()->GetActorLocation().Y < -1500)
	{
		isLeft = true;
	}
}


// Called every frame
void UZombieFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (Me->bZombieDie == false && Me->bZombieHit == false)
	{
		switch (mState)
		{
		case EZombieState::Move:
			MoveState();
			break;
		case EZombieState::Chase:
			ChaseState();
			break;
			
		case EZombieState::Attack:
			AttackState();
			break;
		// case EZombieState::Damage:
		// 	DamageState();
		// 	break;
		// case EZombieState::Die:
		// 	break;
		}
	}

	if (Me->bZombieDie)
	{
		DieState();
	}
}

void UZombieFSM::MoveState()
{
	//Me->GetCharacterMovement()->MaxWalkSpeed = 300;

	FVector TargetLoc = Target->GetActorLocation();
	double PlayerDist = 999999;
	// 플레이어 - 에너미
	for (int i = 0; i < Players.Num(); i++)
	{
		auto Dist = FVector::Distance(Players[i]->GetActorLocation(), Me->GetActorLocation());
		if (PlayerDist > Dist)
		{
			PlayerDist = Dist;
			TargetPlayerNum = i;
		}
	}
	
	// FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();
	if (bFlagDoOnce == false && GetOwner()->HasAuthority())
	{
		if (isLeft)
		{
			ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-1010.0, -2990.0f, -20.0f), FVector(-2460.0,-990.0f,0.0f)));
		}
		else
		{
			ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-910.0f,-6480.0f,0.0f), FVector(-910.0f,-1030.0f,0.0f)));
		}
		bFlagDoOnce = true;
	}
	
	if (Temp2 == 0 && Me->GetActorLocation().X < FirstStop.X+100 && GetOwner()->HasAuthority())
	{
		ai->MoveToLocation(TargetLoc);
	}

	if (PlayerDist<ChaseRange)
	{
		mState = EZombieState::Chase;
		Anim->AnimState = mState;
	}
}

void UZombieFSM::ChaseState()
{
	FVector PlayerLoc = Players[TargetPlayerNum]->GetActorLocation();
	FVector PlayerDir = PlayerLoc - Me->GetActorLocation();

	if (GetOwner()->HasAuthority())
	{
		ai->MoveToLocation(PlayerLoc);
	}
	
	if (PlayerDir.Size()<AttackRange)
	{
		mState = EZombieState::Attack;
		Anim->AnimState = mState;
		CurrentTime = AttackTime;
		//Me->GetCharacterMovement()->MaxWalkSpeed = 0;
	}
}

void UZombieFSM::AttackState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > AttackTime)
	{
		CurrentTime = 0;
		Anim->bAttackPlay = true;
	}
	
	FVector PlayerDir = Players[TargetPlayerNum]->GetActorLocation() - Me->GetActorLocation();
	if (PlayerDir.Size()>AttackRange)
	{
		mState = EZombieState::Move;
		Anim->AnimState = mState;
		//Me->GetCharacterMovement()->MaxWalkSpeed = 300;
	}
}

/*void UZombieFSM::DamageState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > DamageTime)
	{
		mState = EZombieState::Move;
		Me->GetCharacterMovement()->MaxWalkSpeed = 300;
		CurrentTime = 0;
		Anim->AnimState = mState;	
	}
	
}*/

void UZombieFSM::DieState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	
	if (CurrentTime > DeathTime)
	{
		Me->Destroy();
	}
}


FVector UZombieFSM::GetRandomLocationInNavMesh(bool& bisLeft, FVector DestLoc, FVector RightDestLoc)
{
	//FVector Origin;
	//FVector BoxExtent(500.0f, 500.0f, 0.0f);  // 원하는 영역 크기 설정

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (bisLeft)
	{
		if (NavSystem)
		{
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(DestLoc, 500, RandomLocation))
			{
				FirstStop = RandomLocation.Location;
				return RandomLocation.Location;
			}
		}
		// 기본적으로 원점 반환
		return DestLoc;
	}
	else
	{
		if (NavSystem)
		{
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(RightDestLoc, 500, RandomLocation))
			{
				FirstStop = RandomLocation.Location;
				return RandomLocation.Location;
			}
		}
		// 기본적으로 원점 반환
		return RightDestLoc;
	}
	
	
}

//return FVector(-910.0f,-1030.0f,0.0f);
