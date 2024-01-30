// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "PlayerBaseComp_YMH.h"
#include "PlayerFireComp_YMH.generated.h"

class ABullet_YMH;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_Zoom;

	// 맞은 대상이 폰일 때 생기는 이펙트
	UPROPERTY(EditDefaultsOnly, Category="WeaponEffect")
	UParticleSystem* bulletMark;

	UPROPERTY(EditDefaultsOnly, Category="WeaponEffect")
	UParticleSystem* defaultBulletMark;

	UPROPERTY(EditDefaultsOnly, Category="WeaponEffect")
	UParticleSystem* muzzleFire;

	UPROPERTY(EditDefaultsOnly, Category="WeaponEffect")
	UMaterialInstance* bulletDecal;

	FTimerHandle combatHandle;
	
public:
	// ------------------------ Bullet ---------------------------
	UPROPERTY()
	int32 MaxBulletCount;
	int32 reloadBulletCount;
	UPROPERTY()
	int32 bulletCount;
	FVector decalSize;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet_YMH> BulletFactory;

	FVector bulletDropPoint;

public:
	// ------------------------ Weapon Info ------------------------
	int32 weaponeGrade;
	void weaponeUpgrade();
	float Damage;
	float attackDistance;
	float attackSpeed;
	
	float MaxRecoilValue;
	float MinRecoilValue;
	float crosshairRecoilValue;

public:
	// ------------------------ weapon action -------------------------
	void Fire(const FInputActionValue& value);
	void Reload(const FInputActionValue& value);
	
	void ZoomIn(const FInputActionValue& value);
	void ZoomOut(const FInputActionValue& value);
	bool bZoomIn = false;

	float defaultFOV = 90.0f;
	UPROPERTY(EditAnywhere, Category="MySettings")
	float maxFOV = 50.0f;
	
	// ------------------- multi Play --------------------------
	UFUNCTION(Server, Reliable)
	void ServerRPCFire();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCFire(bool bHit, bool bHitZombie, const FHitResult& hitInfo, const FHitResult& hitInfoZombie, const int bc, FTransform firePosition);
	UFUNCTION(Client, Reliable)
	void ClientRPCFire(const int bc);

	UFUNCTION(Server, Reliable)
	void ServerRPCReload();
	UFUNCTION(Client, Reliable)
	void ClientRPCReload();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCReload();
	UFUNCTION(Server, Reliable)
	void ServerRPCInitAmmo();
	UFUNCTION(Client, Reliable)
	void ClientRPCInitAmmo(const int bc);

	UPROPERTY()
	APlayerController_YMH* localPlayer;
};
