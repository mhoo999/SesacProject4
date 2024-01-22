// zombie must die


#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"
#include "ZombieAnim.h"
#include "Blueprint/UserWidget.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "GameFramework/CharacterMovementComponent.h"


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
	ZombieHPUI = CreateWidget(GetWorld(), ZombieHPUIFactory);

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AZombieBase_KJY::OnAttackBeginOverlap);

	Anim = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
}

void AZombieBase_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombieBase_KJY::Damage()
{
	ZombieHPUI->AddToViewport();

	GetCharacterMovement()->MaxWalkSpeed = 0;

	//auto Anim = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
	Anim->PlayDamageAnim();
	
	//CurrentHp -= HP;
	UE_LOG(LogTemp, Warning, TEXT("Damage"));
	if(	CurrentHp <= 0)
	{
		Die();
	}
}

void AZombieBase_KJY::Die()
{
	GetCharacterMovement()->MaxWalkSpeed = 0;

	//auto Anim = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
	Anim->PlayDieAnim();

	Destroy();

}

void AZombieBase_KJY::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerBase_YMH>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("Attack!"));

	if (player&&Anim->bAttackCollision == true)
	{
		player->BeShot(1.0f);
		Anim->bAttackCollision = false;
	}
	// if (player == false)
	// {
	// 	return;
	// }
}
