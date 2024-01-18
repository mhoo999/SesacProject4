// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance_YMH.generated.h"

class APlayerBase_YMH;
/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UPlayerAnimInstance_YMH : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyAnimSettings")
	float direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyAnimSettings")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyAnimSettings")
	bool bIsCombat = false;

	UPROPERTY()
	APlayerBase_YMH* Player;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	// 총쏘기 몽타주
	UPROPERTY(EditDefaultsOnly, Category="Anim")
	UAnimMontage* fireMontage;
	void PlayFireAnimation();

	UFUNCTION()
	void AnimNotify_EndFireDispatcher();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MySettings")
	float pitchAngle;

	// 재장전 몽타주
	UPROPERTY(EditDefaultsOnly, Category="Anim")
	UAnimMontage* reloadMontage;
	void PlayReloadAnimation();
	UFUNCTION()
	void AnimNotify_Reload();

	
};
