// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieFSM.generated.h"

UENUM(BlueprintType)
enum class EZombieState : uint8 { Move, Chase, Attack, };

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

	virtual void MoveState();
	virtual void ChaseState();
	void AttackState();
	//void DamageState();
	void DieState();

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class ADestinationActor_KJY* Target;

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class APlayerBase_YMH* Player;

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class AZombieBase_KJY* Me;

	UPROPERTY(EditAnywhere, Category=FSM)
	float ChaseRange = 300.0f;
	
	UPROPERTY(EditAnywhere, Category=FSM)
	float AttackRange = 100.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float CurrentTime = 0;

	// 공격 대기 시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float AttackTime = 2.0f;

    	
	// 피격 대기 시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float DamageTime = 2.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float DeathTime = 5.0f;

	UPROPERTY()
	class UZombieAnim* Anim;

	UPROPERTY()
	class AAIController* ai;
	
	FVector GetRandomLocationInNavMesh(bool& bisLeft, FVector DestLoc, FVector RightDestLoc);

	bool bFlagDoOnce;

	bool isLeft;

	int32 Temp2;

	FVector FirstStop;

	// ---- LDJ Code -----
	UPROPERTY()
	TArray<AActor*> Players;

	UPROPERTY()
	TArray<FVector> PlayerLocs;

	int32 TargetPlayerNum;

	FTimerHandle ZombieFSM_Handle;

};
