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
	class USkeletalMeshComponent* SpikeMeshComp;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void UpgradeCost() override;
	virtual void UpgradeAbility() override;
	virtual void ReactTrap() override;

	FTimerHandle THandle;

	bool GoalArrived = false;
};
