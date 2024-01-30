// zombie must die


#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"
#include "ZombieAnim.h"
#include "Actor/HealthItem_KJY.h"
#include "Actor/SkillUpItem_KJY.h"
#include "Actor/WalletItem_KJY.h"
#include "Blueprint/UserWidget.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HPWidget_KJY.h"


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
	if (HPWidget != nullptr)
	{
		ZombieHPUI = CreateWidget<UHPWidget_KJY>(GetWorld(), HPWidget);
	}

	CurrentHp = MaxHp;

	
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AZombieBase_KJY::OnAttackBeginOverlap);

	Anim = Cast<UZombieAnim>(GetMesh()->GetAnimInstance());
}

void AZombieBase_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombieBase_KJY::ServerRPCDamage_Implementation(float getDamage)
{
	if (ZombieHPUI != nullptr)
	{
		ZombieHPUI->AddToViewport();
		//ZombieHPUI->SetPercent(CurrentHp, MaxHp);
	}
	
	CurrentHp -= getDamage;

	if(	CurrentHp <= 0)
	{
		MultiDieProcess(CurrentHp);
	}
	else
	{
		MultiRPCDamage(CurrentHp);
	}
}

void AZombieBase_KJY::MultiDieProcess_Implementation(float hp)
{
	SpawnLoc = GetActorLocation() + FVector(0, 0, -50);
	CurrentHp = hp;
	bZombieDie = true;
	GetCharacterMovement()->MaxWalkSpeed = 0;
	SetActorLocation(SpawnLoc);
	PrintHP();
	GetMesh()->SetCollisionProfileName(FName("DieZombie"));

	ServerRPCSpawnItem(SpawnLoc);
}

void AZombieBase_KJY::MultiRPCDamage_Implementation(float hp)
{
	bZombieHit = true;
	
	CurrentHp = hp;
	GetCharacterMovement()->MaxWalkSpeed = 0;
	PrintHP();

	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentHp);
}

void AZombieBase_KJY::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerBase_YMH>(OtherActor);

	if (player&&Anim->bAttackCollision == true)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ATKSound);
		player->BeShot(1.0f);
		Anim->bAttackCollision = false;
	}
	// if (player == false)
	// {
	// 	return;
	// }
}

void AZombieBase_KJY::PrintHP()
{
	if (ZombieHPUI != nullptr)
	{
		ZombieHPUI->HPText->SetText(FText::AsNumber(CurrentHp));
	}
}

void AZombieBase_KJY::ServerRPCSpawnItem_Implementation(FVector sLoc)
{
	const int32 RandItem = FMath::RandRange(0,10);

	if(0 <= RandItem && RandItem < 2)
	{
		// MultiRPCSpawnHealth(sLoc);
		GetWorld()->SpawnActor<AHealthItem_KJY>(HealthFactory, sLoc, FRotator(0));
	}
	else if(2 <= RandItem && RandItem < 4)
	{
		// MultiRPCSpawnSkill(sLoc);
		GetWorld()->SpawnActor<ASkillUpItem_KJY>(SkillUpFactory, sLoc, FRotator(0));
	}
	else
	{
		// MultiRPCSpawnMonny(sLoc);
		GetWorld()->SpawnActor<AWalletItem_KJY>(WalletFactory, sLoc, FRotator(0));
	}
}

void AZombieBase_KJY::MultiRPCSpawnHealth_Implementation(FVector sLoc)
{
	UE_LOG(LogTemp, Warning, TEXT("health Item"));

	GetWorld()->SpawnActor<AHealthItem_KJY>(HealthFactory, sLoc, FRotator(0));
}

void AZombieBase_KJY::MultiRPCSpawnSkill_Implementation(FVector sLoc)
{
	UE_LOG(LogTemp, Warning, TEXT("skill Item"));

	GetWorld()->SpawnActor<ASkillUpItem_KJY>(SkillUpFactory, sLoc, FRotator(0));
}

void AZombieBase_KJY::MultiRPCSpawnMonny_Implementation(FVector sLoc)
{
	UE_LOG(LogTemp, Warning, TEXT("monny Item"));

	GetWorld()->SpawnActor<AWalletItem_KJY>(WalletFactory, sLoc, FRotator(0));
}

