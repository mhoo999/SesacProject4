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

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FSM)
	EZombieState AnimState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	bool bAttackPlay = false;

	UPROPERTY(EditDefaultsOnly, Category=Anim)
	class UAnimMontage* DamageAnimMontage;
	void PlayDamageAnim();

	UPROPERTY(EditDefaultsOnly, Category=Anim)
	class UAnimMontage* DieAnimMontage;
	void PlayDieAnim();

	UFUNCTION(BlueprintCallable)
	void OnEndAttackAnimation();

	UFUNCTION()
	void AnimNotify_Attack();

	UPROPERTY()
	class AZombieBase_KJY* Me;


	bool bAttackCollision;

	UFUNCTION()
	void AnimNotify_ReactEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyAnimSettings")
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyAnimSettings")
	bool bIsDamage;
};
