// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieFSM.generated.h"

UENUM(BlueprintType)
enum class EZombieState : uint8 { Move, Chase, Attack, Damage, Die, };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UZombieFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZombieFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FSM)
	EZombieState mState = EZombieState::Move;

	void MoveState();
	void ChaseState();
	void AttackState();
	void DamageState();
	void DieState();
	// Enemy Hp 감소 함수
	void Damage();

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class ADestinationActor_KJY* Target;

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class APlayerBase_YMH* Player; // 추후 클래스 변경

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class AZombieBase_KJY* Me;

	UPROPERTY(EditAnywhere, Category=FSM)
	float ChaseRange = 1000.0f;
	
	UPROPERTY(EditAnywhere, Category=FSM)
	float AttackRange = 100.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float CurrentTime = 0;

	// 공격 대기 시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float AttackTime = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	float Hp = 3.0f;

	// 피격 대기 시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float DamageTime = 2.0f;

	UPROPERTY()
	class UZombieAnim* Anim;

	UPROPERTY()
	class AAIController* ai;	
};
