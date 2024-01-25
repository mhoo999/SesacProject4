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

	UPROPERTY(EditDefaultsOnly, Category="WeaponEffect")
	UParticleSystem* bulletMark;

	UPROPERTY(EditDefaultsOnly, Category="WeaponEffect")
	UParticleSystem* defaultBulletMark;

	FTimerHandle combatHandle;
	
public:
	// ------------------------ Bullet ---------------------------
	UPROPERTY()
	int32 MaxBulletCount;
	int32 reloadBulletCount;
	UPROPERTY()
	int32 bulletCount;
	
	// ------------------------ Weapon Info ------------------------
	int32 weaponeGrade;
	float Damage;
	float attackDistance;
	float attackSpeed;
	
	float MaxRecoilValue;
	float MinRecoilValue;
	float crosshairRecoilValue;

	// ------------------------ weapon action -------------------------
	void Fire(const FInputActionValue& value);
	void Reload(const FInputActionValue& value);
	UFUNCTION(Server, Reliable)
	void ServerRPCInitAmmo();
	UFUNCTION(Client, Reliable)
	void ClientRPCInitAmmo(const int bc);
	
	// ------------------- multi Play --------------------------
	UFUNCTION(Server, Reliable)
	void ServerRPCFire();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCFire(bool bHit, const FHitResult& hitInfo, const int bc);
	UFUNCTION(Client, Reliable)
	void ClientRPCFire(const int bc);

	UFUNCTION(Server, Reliable)
	void ServerRPCReload();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCReload();
};
