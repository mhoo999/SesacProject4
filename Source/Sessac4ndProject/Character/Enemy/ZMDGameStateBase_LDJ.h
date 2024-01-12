// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ZMDGameStateBase_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AZMDGameStateBase_LDJ : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Life")
	int32 Life = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Life")
	int32 KillZombieGoal = 5;

	UFUNCTION()
	void GameJudge();
};
