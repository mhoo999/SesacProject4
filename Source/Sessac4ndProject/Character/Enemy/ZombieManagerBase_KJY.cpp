// zombie must die


#include "Character/Enemy/ZombieManagerBase_KJY.h"

#include "Character/Enemy/ZombieBase_KJY.h"


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

	StartSpawning();
}

// Called every frame
void AZombieManagerBase_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieManagerBase_KJY::StartSpawning()
{
	float CreateTime = FMath::RandRange(MinTime, MaxTime);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AZombieManagerBase_KJY::CreateZombie, CreateTime, true, CreateTime);
}

void AZombieManagerBase_KJY::StopSpawning()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

void AZombieManagerBase_KJY::CreateZombie()
{
	int32 RandomValue = FMath::RandRange(0, ZombieFactoryArray.Num() - 1);
	
	if (SpawnCount < MaxSpawnCount)
	{
		auto tempX = GetActorLocation().X;
		auto tempY = GetActorLocation().Y;
		RandSpawnX = FMath::RandRange(tempX - 100, tempX + 100);
		RandSpawnY = FMath::RandRange(tempY - 500, tempY + 500);
		FVector TempVec = FVector(RandSpawnX, RandSpawnY, 0);
		GetWorld()->SpawnActor<AZombieBase_KJY>(ZombieFactoryArray[RandomValue], TempVec, FRotator(0));

		SpawnCount++;

		if (SpawnCount >= MaxSpawnCount)
		{
			StopSpawning();
		}
	}
}