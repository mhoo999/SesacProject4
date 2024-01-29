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
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category=FSM)
	EZombieState mState = EZombieState::Move;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void MoveState();
	void ChaseState();
	void AttackState();
	//void DamageState();
	//void DieState();

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class ADestinationActor_KJY* Target;

	UPROPERTY(Replicated, VisibleAnywhere, Category=FSM)
	class APlayerBase_YMH* Player;

	UPROPERTY(Replicated, VisibleAnywhere, Category=FSM)
	class AZombieBase_KJY* Me;

	UPROPERTY(Replicated, EditAnywhere, Category=FSM)
	float ChaseRange = 300.0f;
	
	UPROPERTY(Replicated, EditAnywhere, Category=FSM)
	float AttackRange = 150.0f;

	UPROPERTY(Replicated, EditAnywhere, Category=FSM)
	float CurrentTime = 0;

	// 공격 대기 시간
	UPROPERTY(Replicated, EditAnywhere, Category=FSM)
	float AttackTime = 2.0f;

    	
	// 피격 대기 시간
	UPROPERTY(Replicated, EditAnywhere, Category=FSM)
	float DamageTime = 2.0f;

	UPROPERTY(Replicated, EditAnywhere, Category=FSM)
	float DeathTime = 1.0f;

	UPROPERTY(Replicated)
	class UZombieAnim* Anim;

	UPROPERTY(Replicated)
	class AAIController* ai;
	
	FVector GetRandomLocationInNavMesh(bool& bisLeft, FVector DestLoc, FVector RightDestLoc);

	UPROPERTY(Replicated)
	bool bFlagDoOnce;

	UPROPERTY(Replicated)
	bool isLeft;

	int32 Temp2;

	UPROPERTY(Replicated)
	FVector FirstStop;

	UPROPERTY(Replicated)
	FVector PlayerDir;

	UFUNCTION(Server, Reliable)
	void ServerRPC_ChaseState();

	UFUNCTION(Client, Reliable)
	void ClientRPC_ChaseState();

	 
};