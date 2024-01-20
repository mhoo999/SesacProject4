// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase_YMH.generated.h"

class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SESSAC4NDPROJECT_API ACharacterBase_YMH : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase_YMH();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stat")
	float maxHelth;
	
	// 현재 체력
	UPROPERTY(BlueprintReadOnly, Category="Stat")
	float currentHealth;

	// 공격 속도
	float attackSpeed;

	// 데미지
	float Damage;

	// 공격 사정거리
	float attackDistance;

public:
	// 공격
	virtual void Attack();

	// 피격
	UFUNCTION(BlueprintCallable)
	virtual void BeShot(float damage);
	bool bIsDead = false;

	// 체력 회복
	virtual void RestorationHealth();
};
