

#include "Character/Enemy/ZombieManagerBase_KJY.h"

#include "FastZombie_KJY.h"
#include "TankerZombie_KJY.h"
#include "Zombie_KJY.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Net/UnrealNetwork.h"
#include "UI/WaveInformationUI_LDJ.h"


AZombieManagerBase_KJY::AZombieManagerBase_KJY()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombieManagerBase_KJY::BeginPlay()
{
	Super::BeginPlay();

	float CreateTime = FMath::RandRange(MinTime, MaxTime);
	// GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AZombieManagerBase_KJY::CreateZombie, CreateTime);
	// GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void AZombieManagerBase_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentTime = CurrentTime + DeltaTime;
	if (CurrentTime > RandomTimeNum)
	{
		CurrentTime = 0;
		RandomTimeNum = FMath::RandRange(MinTime, MaxTime);
		NewCreateZombie();
	}
}

// void AZombieManagerBase_KJY::CreateZombie()
// {
// 	auto tempX = GetActorLocation().X;
// 	auto tempY = GetActorLocation().Y;
// 	RandSpawnX = FMath::RandRange(tempX - 100, tempX + 100);
// 	RandSpawnY = FMath::RandRange(tempY - 100, tempY + 100);
// 	FVector TempVec = FVector(RandSpawnX, RandSpawnY, 100);
// 	
// 	//첫번째 웨이브
// 	if (Wave1 && CurrentWave == 1) 
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("%f"), (float)TempVec.Z));
// 		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave1--;
// 	}
// 	else if (!Wave1 && CurrentWave == 1)
// 	{
// 		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
// 		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave1 Spawn End")); 
// 	}
// 	
// 	//두번째 웨이브
// 	if (!Wave1&&Wave2&&CurrentWave == 2)
// 	{
// 		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave2--;
// 		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave2--;
// 		GetWorld()->SpawnActor<ATankerZombie_KJY>(TankerZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave2--;
// 	}
// 	else if (!Wave1&&!Wave2&& CurrentWave == 2)
// 	{
// 		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
// 		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave2 Spawn End")); 
// 	}
// 	
// 	//세번째 웨이브
// 	if (!Wave1&&!Wave2&&Wave3&& CurrentWave == 3)
// 	{
// 		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave3--;
// 		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave3--;
// 		GetWorld()->SpawnActor<ATankerZombie_KJY>(TankerZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave3--;
// 		GetWorld()->SpawnActor<AFastZombie_KJY>(FastZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
// 		Wave3--;
// 	}
// 	else if (!Wave1&&!Wave2&&!Wave3&& CurrentWave == 3)
// 	{
// 		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
// 		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave3 Spawn End")); 
// 	}
// 	
// 	float CreateTime = FMath::RandRange(MinTime, MaxTime);
// 	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AZombieManagerBase_KJY::CreateZombie, CreateTime);
// }

void AZombieManagerBase_KJY::NewCreateZombie()
{
	if (CurrentWave > 4)
	{
		return;
	}
	
	RandSpawnLoc_X = GetActorLocation().X;
	RandSpawnLoc_Y = GetActorLocation().Y;
	RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
	RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
	FVector TempVec = FVector(RandSpawnX, RandSpawnY, 100);

	//첫번째 웨이브
	if (Wave1 && CurrentWave == 1) // Wave1 ing
	{
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		Wave1--;
	}
	else if (!Wave1 && CurrentWave == 1) // Wave1 End
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave1 Spawn End")); 
	}
	
	//두번째 웨이브
	if (!Wave1&&Wave2&&CurrentWave == 2) // Wave2 ~ing
	{
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
		RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
		Wave2--;
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
		RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
		Wave2--;
		GetWorld()->SpawnActor<ATankerZombie_KJY>(TankerZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
		RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
		Wave2--;
	}
	else if (!Wave1&&!Wave2&& CurrentWave == 2) // Wave2 끝
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave2 Spawn End")); 
	}
	
	//세번째 웨이브
	if (!Wave1&&!Wave2&&Wave3&& CurrentWave == 3) // Wave3 도중
	{
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
		RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
		Wave3--;
		GetWorld()->SpawnActor<AZombie_KJY>(ZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
		RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
		Wave3--;
		GetWorld()->SpawnActor<ATankerZombie_KJY>(TankerZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
		RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
		Wave3--;
		GetWorld()->SpawnActor<AFastZombie_KJY>(FastZombieFactory, TempVec, FRotator(0), ActorSpawnParameters);
		RandSpawnX = FMath::RandRange(RandSpawnLoc_X - 100, RandSpawnLoc_X + 100);
		RandSpawnY = FMath::RandRange(RandSpawnLoc_Y - 200, RandSpawnLoc_Y + 200);
		Wave3--;
	}
	else if (!Wave1&&!Wave2&&!Wave3&& CurrentWave == 3) // Wave3 끝
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimerHandle);
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Wave3 Spawn End")); 
	}
}

