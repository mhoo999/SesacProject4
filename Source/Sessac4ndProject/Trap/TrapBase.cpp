// zombie must die


#include "TrapBase.h"

#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/Zombie_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Components/BoxComponent.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Character/Player/PlayerUpgradeComp_YMH.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerController_YMH.h"

// Sets default values
ATrapBase::ATrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Building Component"));
	SetRootComponent(BuildingCollision);
	BuildingCollision->SetBoxExtent(FVector(186,186,25));
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh Component"));
	TileMesh->SetupAttachment(RootComponent);
	TileMesh->SetRelativeScale3D(FVector(2.25,2.25,1));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileMeshRef(TEXT("/Game/SimpleApocalypse/Meshes/Environment/SM_Env_ManholeClosed_01.SM_Env_ManholeClosed_01"));
    if (TileMeshRef.Object)
    {
		TileMesh->SetStaticMesh(TileMeshRef.Object);
    }
	ReactionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Sensing Component"));
	ReactionCollision->SetupAttachment(RootComponent);
	ReactionCollision->SetBoxExtent(FVector(129));

	static ConstructorHelpers::FObjectFinder<USoundBase> ReactFlameTrapSoundRef(TEXT("/Game/Resources/LDJ/Sounds/Trap/FireTrap_React.FireTrap_React"));
	ReactFlameTrapSound = ReactFlameTrapSoundRef.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> ReactFreezeTrapSoundRef(TEXT("/Game/Resources/LDJ/Sounds/Trap/FreezeTrap_React.FreezeTrap_React"));
	ReactFreezeTrapSound = ReactFreezeTrapSoundRef.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> ReactSpikeTrapSoundRef(TEXT("/Game/Resources/LDJ/Sounds/Trap/SpikeTrap_React.SpikeTrap_React"));
	ReactSpikeTrapSound = ReactSpikeTrapSoundRef.Object;

	

	bReplicates = true;
}

// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	ReactionCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrapBase::OnEnemyBeginOverlapped);
	ReactionCollision->OnComponentEndOverlap.AddDynamic(this, &ATrapBase::OnEnemyEndOverlapped);
	Player = Cast<APlayerBase_YMH>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	auto pc = Cast<APlayerController_YMH>(GetWorld()->GetFirstPlayerController());
	PlayerUpgradeComp = Player->FindComponentByClass<UPlayerUpgradeComp_YMH>();
	if (pc)
	{
		SetOwner(pc);
	}
}

// Called every frame
void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrapBase::OnEnemyBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TO DO : 플레이어한테 반응하는거 에너미로 바꾸기
	auto Temp = Cast<AZombieBase_KJY>(OtherActor);
	if (Temp)
	{
		TrapInArea++;
		EnemyArray.Push(Temp);
		for (auto e : EnemyArray) UE_LOG(LogTemp,Warning, TEXT("%p"), e->fsm)
	}
	if (!GetWorld()->GetTimerManager().IsTimerActive(Handle))
	{
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this]()-> void
		{
			if (TrapInArea == 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(Handle);	
			}
			else
			{
				ReactTrap(EnemyArray);
			}
		}), AttackCoolTime, true, 0);
	}
}

void ATrapBase::OnEnemyEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Temp = Cast<AZombieBase_KJY>(OtherActor);
	if (Temp)
	{
		TrapInArea--;
		auto idx = EnemyArray.Find(Temp);
		EnemyArray[idx]->CustomTimeDilation = 1;
		EnemyArray.RemoveAt(idx);
	}
}

int32 ATrapBase::GetCost()
{
	return Cost;
}

void ATrapBase::UpgradeAbility()
{
}

void ATrapBase::ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef)
{
}

