// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Trap/TrapBase.h"
#include "FlameThrowerTrap_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AFlameThrowerTrap_LDJ : public ATrapBase
{
	GENERATED_BODY()

public:
	AFlameThrowerTrap_LDJ();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FireFX1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FireFX2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FireFX3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* FireFX4;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual int32 GetCost() override;
	virtual void UpgradeAbility() override;
	virtual void ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef) override;

	FTimerHandle THandle;

	bool GoalArrived = false;
};
