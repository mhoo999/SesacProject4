// zombie must die


#include "Character/Enemy/ZombieManagerBase_KJY.h"

#include "Zombie_KJY.h"


// Sets default values
AZombieManagerBase_KJY::AZombieManagerBase_KJY()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AZombieManagerBase_KJY::BeginPlay()
{
	Super::BeginPlay();

	float CreateTime = FMath::RandRange(MinTime, MaxTime);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AZombieManagerBase_KJY::CreateZombie, CreateTime);
	GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
}

// Called every frame
void AZombieManagerBase_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieManagerBase_KJY::CreateZombie()
{
	UE_LOG(LogTemp, Warning, TEXT("zombie"));
	auto tempX = GetActorLocation().X;
	auto tempY = GetActorLocation().Y;
	RandSpawnX = FMath::RandRange(tempX - 100, tempX + 100);
	RandSpawnY = FMath::RandRange(tempY - 500, tempY + 500);
	FVector TempVec = FVector(RandSpawnX, RandSpawnY, 0);
	if (Wave1)
	{
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0));
		Wave1--;
	}
	float CreateTime = FMath::RandRange(MinTime, MaxTime);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AZombieManagerBase_KJY::CreateZombie, CreateTime);
}

