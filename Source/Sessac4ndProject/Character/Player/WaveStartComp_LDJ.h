// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/Player/PlayerBaseComp_YMH.h"
#include "WaveStartComp_LDJ.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UWaveStartComp_LDJ : public UPlayerBaseComp_YMH
{
	GENERATED_BODY()
	UWaveStartComp_LDJ();
	
public:
	// ----- 상속받은 함수 -----
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

	// ----- 만들어준 함수 -----
	void WaveStart(const FInputActionValue& value);
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_WaveStart();
	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WaveStart(int32 WaveNum);
	
	// ----- UPROPERTY 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	class UInputAction* IA_WaveStart;

	UPROPERTY()
	class AZombieManagerBase_KJY* ZombieSpawnManager; // 웨이브 시스템

	UPROPERTY()
	TArray<AActor*> ZombieManagerArray; // 웨이브 시스템

	UPROPERTY()
	TArray<AActor*> LivingZombieArray;

	UPROPERTY()
	class APlayerController_YMH* MyPlayerController;

	UPROPERTY()
	class AZombieManagerBase_KJY* Temp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* WaveReadySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* WaveStartSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* GameWinSound;

	UPROPERTY()
	class UAudioComponent* SoundController;

	// ----- 일반 변수 -----
	FTimerHandle ZombieDieHandle;
	FTimerHandle WinHandle;
	FTimerHandle TextHandle;
	
	bool bWaveClear = true;

};
