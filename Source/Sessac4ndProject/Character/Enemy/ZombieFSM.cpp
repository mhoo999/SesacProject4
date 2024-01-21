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
	auto Playeractor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerBase_YMH::StaticClass());
	Player = Cast<APlayerBase_YMH>(Playeractor);
	Me = Cast<AZombieBase_KJY>(GetOwner());

	Anim = Cast<UZombieAnim>(Me->GetMesh()->GetAnimInstance());

	ai = Cast<AAIController>(Me->GetController());

	if (GetOwner()->GetActorLocation().Y < )
	{
		isLeft = true;
	}
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
	case EZombieState::Chase:
		ChaseState();
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
	FVector TargetLoc = Target->GetActorLocation();
	// 목적지 - 에너미
	FVector TargetDir = TargetLoc - Me->GetActorLocation();
	// 플레이어 - 에너미
	FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();

	if (bFlagDoOnce == false)
	{
		if (isLeft)
		{
			//ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-910.0f,-6480.0f,0.0f), FVector(-910.0f,-1030.0f,0.0f)));
			//ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-2460.0, -2990.0f, -20.0f), FVector(-2460.0,-990.0f,0.0f)));
			ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-1010.0, -2990.0f, -20.0f), FVector(-2460.0,-990.0f,0.0f)));
		}
		else
		{
			ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-910.0f,-6480.0f,0.0f), FVector(-910.0f,-1030.0f,0.0f)));
		}
		bFlagDoOnce = true;
	}
	
	if (Temp2 == 0 && Me->GetActorLocation().X < FirstStop.X+100)
	{
		// 첫번째 경유지에 도착했을때 다음 경유지로 간다
		//ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-910.0f,-3240.0f,0.0f),FVector(-910.0f,-3240.0f,0.0f)));
		ai->MoveToLocation(	 GetRandomLocationInNavMesh(isLeft, FVector(-7030.0f, -2070.0f, 0.0f),FVector(-7030.0f, -2070.0f, 0.0f)));
		//Temp2++;
		//ai->MoveToLocation(TargetLoc);

	}
		

	// 목적지 향해 가다가
	//Me->AddMovementInput(TargetDir.GetSafeNormal());

	if (PlayerDir.Size()<ChaseRange)
	{
		mState = EZombieState::Chase;
		Anim->AnimState = mState;
	}
}

void UZombieFSM::ChaseState()
{
	FVector PlayerLoc = Player->GetActorLocation();
	FVector PlayerDir = PlayerLoc - Me->GetActorLocation();

	ai->MoveToLocation(PlayerLoc);
	
	if (PlayerDir.Size()<AttackRange)
	{
		mState = EZombieState::Attack;
		Anim->AnimState = mState;
		CurrentTime = AttackTime;
		Me->GetCharacterMovement()->MaxWalkSpeed = 0;
	}
	
}

void UZombieFSM::AttackState()
{
	//ai->SetFocus(Player, EAIFocusPriority::Gameplay);

	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > AttackTime)
	{
		CurrentTime = 0;
		Anim->bAttackPlay = true;

		/*if (플레이어와 닿으면  )
		{
			//FHitOverlap
			// 플레이어 체력 닳음
		}*/
	}
	
	FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();
	if (PlayerDir.Size()>AttackRange)
	{
		mState = EZombieState::Move;
		Anim->AnimState = mState;
		Me->GetCharacterMovement()->MaxWalkSpeed = 300;
	}
}

void UZombieFSM::DamageState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > DamageTime)
	{
		mState = EZombieState::Move;
		Me->GetCharacterMovement()->MaxWalkSpeed = 300;
		CurrentTime = 0;
		Anim->AnimState = mState;	
	}
	
}

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
