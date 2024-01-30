// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Trap/TrapBase.h"
#include "FreezeTrap_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AFreezeTrap_LDJ : public ATrapBase
{
	GENERATED_BODY()

public:
	AFreezeTrap_LDJ();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FreezeFX1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FreezeFX2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FreezeFX3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FreezeFX4;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual int32 GetCost() override;
	virtual void UpgradeAbility() override;
	virtual void ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef) override;

	FTimerHandle THandle;

	bool GoalArrived = false;
};
