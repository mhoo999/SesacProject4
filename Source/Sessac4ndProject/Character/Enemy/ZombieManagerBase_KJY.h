// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieManagerBase_KJY.generated.h"

class AZombieBase_KJY;
UCLASS()
class SESSAC4NDPROJECT_API AZombieManagerBase_KJY : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieManagerBase_KJY();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float MinTime = 1;	
	UPROPERTY(EditAnywhere)
	float MaxTime = 3;
	UPROPERTY(EditAnywhere)
	TArray<class AActor*> SpawnPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AZombieBase_KJY>> ZombieFactoryArray;
	
	FTimerHandle SpawnTimerHandle;
	void CreateZombie();

	double RandSpawnX;
	double RandSpawnY;

	UPROPERTY(EditAnywhere)
	int SpawnCount = 0;
	UPROPERTY(EditAnywhere)
	int MaxSpawnCount = 30;
	
	void StartSpawning();
	void StopSpawning();
	
};
