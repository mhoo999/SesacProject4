// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/ZombieFSM.h"
#include "TraceZombieFSM_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UTraceZombieFSM_KJY : public UZombieFSM
{
	GENERATED_BODY()

	
	UPROPERTY(VisibleAnywhere, Category=FSM)
	class AShotgunPlayer_YMH* ShotgunPlayer;
};
