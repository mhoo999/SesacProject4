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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FSM)
	EZombieState AnimState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	bool bAttackPlay = false;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* DamageAnimMontage;
	void PlayDamageAnim();
	
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* DieAnimMontage;
	void PlayDieAnim();
};
