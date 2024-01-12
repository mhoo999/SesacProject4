// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombieFSM.h"
#include "ZombieAnim.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UZombieAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FSM)
	EZombieState State;
	
};
