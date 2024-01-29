// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "TrapBase.h"
#include "SpikeTrap_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API ASpikeTrap_LDJ : public ATrapBase
{
	GENERATED_BODY()

	ASpikeTrap_LDJ();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* SpikeMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* SpikeMeshComp2;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual int32 GetCost() override;
	virtual void UpgradeAbility() override;
	virtual void ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef) override;

	FTimerHandle THandle;

	bool GoalArrived = false;
};
