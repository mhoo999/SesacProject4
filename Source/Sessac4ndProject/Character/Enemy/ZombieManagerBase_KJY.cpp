// zombie must die


#include "Character/Enemy/ZombieManagerBase_KJY.h"

#include "FastZombie_KJY.h"
#include "TankerZombie_KJY.h"
#include "Zombie_KJY.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Net/UnrealNetwork.h"
#include "UI/WaveInformationUI_LDJ.h"


// Sets default values
AZombieManagerBase_KJY::AZombieManagerBase_KJY()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AZombieManagerBase_KJY::BeginPlay()
{
	Super::BeginPlay();

	float CreateTime = FMath::RandRange(MinTime, MaxTime);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AZombieManagerBase_KJY::CreateZombie, CreateTime);
	GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
	SetOwner(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AZombieManagerBase_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieManagerBase_KJY::CreateZombie()
{
	auto tempX = GetActorLocation().X;
	auto tempY = GetActorLocation().Y;
	RandSpawnX = FMath::RandRange(tempX - 100, tempX + 100);
	RandSpawnY = FMath::RandRange(tempY - 500, tempY + 500);
	FVector TempVec = FVector(RandSpawnX, RandSpawnY, 0);
	
	//첫번째 웨이브
	if (Wave1 && CurrentWave == 1) 
	{
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0));
		Wave1--;
	}
	else if (!Wave1 && CurrentWave == 1)
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave1 Spawn End")); 
	}
	//두번째 웨이브
	
	if (!Wave1&&Wave2&&CurrentWave == 2)
	{
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0));
		Wave2--;
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0));
		Wave2--;
		GetWorld()->SpawnActor<ATankerZombie_KJY>(TankerZombieFactory, TempVec, FRotator(0));
		Wave2--;
	}
	else if (!Wave1&&!Wave2&& CurrentWave == 2)
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave2 Spawn End")); 
	}
	//세번째 웨이브
	if (!Wave1&&!Wave2&&Wave3&& CurrentWave == 3)
	{
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0));
		Wave3--;
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0));
		Wave3--;
		GetWorld()->SpawnActor<ATankerZombie_KJY>(TankerZombieFactory, TempVec, FRotator(0));
		Wave3--;
		GetWorld()->SpawnActor<AFastZombie_KJY>(FastZombieFactory, TempVec, FRotator(0));
		Wave3--;
	}
	else if (!Wave1&&!Wave2&&!Wave3&& CurrentWave == 3)
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave3 Spawn End")); 
	}
	
	float CreateTime = FMath::RandRange(MinTime, MaxTime);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AZombieManagerBase_KJY::CreateZombie, CreateTime);
}

