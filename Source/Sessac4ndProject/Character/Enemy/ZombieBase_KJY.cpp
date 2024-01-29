// zombie must die


#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"
#include "ZombieAnim.h"
#include "Actor/HealthItem_KJY.h"
#include "Actor/ItemActor_KJY.h"
#include "Actor/SkillUpItem_KJY.h"
#include "Actor/WalletItem_KJY.h"
#include "Blueprint/UserWidget.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
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

void AZombieBase_KJY::Damage()
{

	GetCharacterMovement()->MaxWalkSpeed = 0;

	if (ZombieHPUI != nullptr)
	{
		ZombieHPUI->AddToViewport();
		//ZombieHPUI->SetPercent(CurrentHp, MaxHp);
	}

	CurrentHp--;
	PrintHP();
	Anim->PlayDamageAnim();
	
	if(	CurrentHp == 0) // <= 에서 ==으로 변경
	{
		SpawnLoc = this->GetActorLocation() + FVector(0, 0, 100);
		UE_LOG(LogTemp, Warning, TEXT("Spawn Loc : %s"), *SpawnLoc.ToString());
		Die();
	}
}

void AZombieBase_KJY::Die()
{
	Anim->PlayDieAnim();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SpawnItem();
	
	auto temp = Cast<AZombieBase_KJY>(GetMesh()->GetOwner());
	temp->GetCharacterMovement()->MaxWalkSpeed = 0;
	// GetWorld()->GetTimerManager().SetTimer(ZombieBaseTimer, FTimerDelegate::CreateLambda([&]
	// {
	// 	Destroy();
	// }), 0.1, false);

}

void AZombieBase_KJY::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerBase_YMH>(OtherActor);

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

void AZombieBase_KJY::PrintHP()
{
	if (ZombieHPUI != nullptr)
	{
		ZombieHPUI->HPText->SetText(FText::AsNumber(CurrentHp));
	}
}

void AZombieBase_KJY::SpawnItem()
{
	float RandItem = FMath::RandRange(0,1);
	// if(RandItem < 0.6)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("SpawnWallet"));
	//
	// 	GetWorld()->SpawnActor<AWalletItem_KJY>(WalletFactory, FVector(0), FRotator(0));
	// 	UE_LOG(LogTemp, Warning, TEXT("Spawn Loc : %s"), *SpawnLoc.ToString());
	// }
	// else if(RandItem<0.8)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("SpawnHelath"));
	// 	
	// 	GetWorld()->SpawnActor<AHealthItem_KJY>(HealthFactory, FVector(0), FRotator(0));
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("SpawnSkillUp"));
	//
	// 	GetWorld()->SpawnActor<ASkillUpItem_KJY>(SkillUpFactory, FVector(0), FRotator(0));
	// }

	GetWorld()->SpawnActor<AWalletItem_KJY>(WalletFactory, SpawnLoc, FRotator(0));
	// GEngine->AddOnScreenDebugMessage(-1,3,FColor::Purple, FString::Printf(TEXT("%f, %f"), e->GetActorLocation().X, e->GetActorLocation().Y));

}

