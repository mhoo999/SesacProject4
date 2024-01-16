// zombie must die


#include "ZombieFSM.h"

#include "AIController.h"
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
	/*case EZombieState::Chase:
		ChaseState();
		break;
		
	case EZombieState::Attack:
		AttackState();
		break;*/
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
	FVector Destination = Target->GetActorLocation();
	// 목적지 - 에너미
	FVector TargetDir = Destination - Me->GetActorLocation();
	// 플레이어 - 에너미
	FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();

	// 목적지 향해 가다가
	//Me->AddMovementInput(TargetDir.GetSafeNormal());
	ai->MoveToLocation(Destination);

	
	if (PlayerDir.Size()<AttackRange)
	{
		mState = EZombieState::Attack;
		Anim->AnimState = mState;
		//Anim->bAttackPlay = true;
		CurrentTime = AttackTime;
	}
}

/*void UZombieFSM::ChaseState()
{
	FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();
	
	if (PlayerDir.Size()<AttackRange)
	{
		mState = EZombieState::Attack;
		Anim->AnimState = mState;
		Anim->bAttackPlay = true;
		CurrentTime = AttackTime;
	}
}*/

void UZombieFSM::AttackState()
{
	
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > AttackTime)
	{
		//ai->SetFocus(Player, EAIFocusPriority::Gameplay); 
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		Anim->AnimState = mState;	
		// 플레이어 공격 에니메이션
		// 플레이어 체력 닳음
		CurrentTime = 0;
		//Anim->bAttackPlay = true;
	}

	FVector PlayerDir = Player->GetActorLocation() - Me->GetActorLocation();
	if (PlayerDir.Size()>AttackRange)
	{
		mState = EZombieState::Move;
		Anim->AnimState = mState;	
	}
}

void UZombieFSM::DamageState()
{
	auto anim = Cast<UZombieAnim>(Me->GetMesh()->GetAnimInstance());
	//anim->PlayDamageAnim();
	
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > DamageTime)
	{
		Me->GetCharacterMovement()->MaxWalkSpeed = 400;
		mState = EZombieState::Move;
		CurrentTime = 0;
		Anim->AnimState = mState;	
	}
	
}

void UZombieFSM::DieState()
{
	auto anim = Cast<UZombieAnim>(Me->GetMesh()->GetAnimInstance());

	if (!anim->Montage_IsPlaying(anim->DieAnimMontage))
	{
		UE_LOG(LogTemp, Warning, TEXT("Die"));
		anim->PlayDieAnim();
		anim->Montage_Play(anim->DieAnimMontage);
	}
	
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > DeathTime)
	{
		Me->Destroy();
	}
}

void UZombieFSM::Damage()
{
	Hp--;
	Me->GetCharacterMovement()->MaxWalkSpeed = 0;
	
	if(Hp>0)
	{
		mState = EZombieState::Damage;

		CurrentTime = 0;
		Anim->AnimState = mState;	
	}
	else
	{
		mState = EZombieState::Die;
	}
	Anim->AnimState = mState;	
}

