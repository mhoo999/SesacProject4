// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "PlayerBaseComp_YMH.h"
#include "PlayerFireComp_YMH.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UPlayerFireComp_YMH : public UPlayerBaseComp_YMH
{
	GENERATED_BODY()
	
public:
	UPlayerFireComp_YMH();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_Reload;

public:
	// 사격
	void Fire(const FInputActionValue& value);
	// bool fireDispatcher;
	
	FTimerHandle combatHandle;
	// void FireBullet();
	// float currentTime = 0;

	UPROPERTY(EditDefaultsOnly, Category="WeaponEffect")
	UParticleSystem* bulletMark;

	// 재장전
	void Reload(const FInputActionValue& value);
	// bool bIsReloading;
};
