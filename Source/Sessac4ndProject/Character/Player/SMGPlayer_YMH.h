// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase_YMH.h"
#include "SMGPlayer_YMH.generated.h"

/**
 * 
 */

UCLASS()
class SESSAC4NDPROJECT_API ASMGPlayer_YMH : public APlayerBase_YMH
{
	GENERATED_BODY()
	
public:
	ASMGPlayer_YMH();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetCrosshair() override;
};
