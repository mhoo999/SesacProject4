// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieManagerBase_KJY.generated.h"

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
	TSubclassOf<class AZombie_KJY> ZombieFactory;
	
	FTimerHandle SpawnTimerHandle;
	void CreateZombie();

	double RandSpawnX;
	double RandSpawnY;
};
