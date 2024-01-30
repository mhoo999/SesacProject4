// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase_YMH.h"
#include "ZombieBase_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AZombieBase_KJY : public ACharacterBase_YMH
{
	GENERATED_BODY()

public:
	AZombieBase_KJY();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UZombieFSM* fsm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FSM)
	float MaxHp = 10.0f;

	UPROPERTY()
	float CurrentHp = MaxHp;
	
	UFUNCTION(Server, Reliable)
	void ServerRPCDamage(float getDamage);
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCDamage(float hp);

	UFUNCTION(NetMulticast, Reliable)
	void MultiDieProcess(float hp);

	bool bZombieHit = false;
	bool bZombieDie = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHPWidget_KJY> HPWidget;
	class UHPWidget_KJY* ZombieHPUI;

	UFUNCTION()
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);

	UPROPERTY()
	class UZombieAnim* Anim;

	void PrintHP();

	UPROPERTY(EditAnywhere)
	FVector SpawnLoc;

	UPROPERTY()
	class AZombieBase_KJY* Me;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWalletItem_KJY> WalletFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHealthItem_KJY> HealthFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASkillUpItem_KJY> SkillUpFactory;
	
	UFUNCTION(Server, Reliable)
	void ServerRPCSpawnItem(FVector sLoc);
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCSpawnHealth(FVector spawnLocation);
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCSpawnSkill(FVector spawnLocation);
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPCSpawnMonny(FVector spawnLocation);

	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* ATKSound;
};
