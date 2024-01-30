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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATankerZombie_KJY> TankerZombieFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AFastZombie_KJY> FastZombieFactory;

	UPROPERTY()
	class UPlayerBuildComp_LDJ* PlayerBuildComp;
	
	FTimerHandle SpawnTimerHandle;
	void CreateZombie();
	void NewCreateZombie();

	double RandSpawnX;
	double RandSpawnY;

	int32 Wave1 = 20; // *2
	int32 Wave2 = 30; // *3
	int32 Wave3 = 40; // *4
	int32 CurrentWave = 0;
	FActorSpawnParameters ActorSpawnParameters;
	// ESpawnActorCollisionHandlingMethod ActorSpawnParams = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ----- LDJ Code -----
	float CurrentTime = 0;
	float RandomTimeNum = 1;
	double RandSpawnLoc_X;
	double RandSpawnLoc_Y;

};
