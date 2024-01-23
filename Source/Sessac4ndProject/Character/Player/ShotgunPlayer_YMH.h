// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "ShotgunPlayer_YMH.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AShotgunPlayer_YMH : public APlayerBase_YMH
{
	GENERATED_BODY()

public:
	AShotgunPlayer_YMH();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetCrosshair() override;
};
