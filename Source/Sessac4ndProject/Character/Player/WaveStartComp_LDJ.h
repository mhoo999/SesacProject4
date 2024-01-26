// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/PlayerBaseComp_YMH.h"
#include "WaveStartComp_LDJ.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UWaveStartComp_LDJ : public UPlayerBaseComp_YMH
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;
};
