// zombie must die


#include "TrapBase.h"

#include "Character/Player/PlayerBase_YMH.h"
#include "Components/BoxComponent.h"

// Sets default values
ATrapBase::ATrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Building Component"));
	SetRootComponent(BuildingCollision);
	BuildingCollision->SetBoxExtent(FVector(142,142,25));
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh Component"));
	TileMesh->SetupAttachment(RootComponent);
	TileMesh->SetRelativeScale3D(FVector(1.775,1.775,1));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileMeshRef(TEXT("/Game/SimpleApocalypse/Meshes/Environment/SM_Env_ManholeClosed_01.SM_Env_ManholeClosed_01"));
    if (TileMeshRef.Object)
    {
		TileMesh->SetStaticMesh(TileMeshRef.Object);
    }
	ReactionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Sensing Component"));
	ReactionCollision->SetupAttachment(RootComponent);
	ReactionCollision->SetBoxExtent(FVector(142));
}

// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	ReactionCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrapBase::OnEnemyBeginOverlapped);
	ReactionCollision->OnComponentEndOverlap.AddDynamic(this, &ATrapBase::OnEnemyEndOverlapped);
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
	auto Temp = Cast<APlayerBase_YMH>(OtherActor);
	if (Temp)
	{
		TrapInArea++;
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
				ReactTrap();
			}
		}), AttackCoolTime, true, 0);
	}
}

void ATrapBase::OnEnemyEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Temp = Cast<APlayerBase_YMH>(OtherActor);
	if (Temp)
	{
		TrapInArea--;
	}
}

void ATrapBase::UpgradeCost()
{
	this->Cost -= 50;
}

void ATrapBase::UpgradeAbility()
{
}

void ATrapBase::ReactTrap()
{
	UE_LOG(LogTemp,Warning, TEXT("Parent Trap"));
}

