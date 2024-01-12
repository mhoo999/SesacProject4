// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieFSM.generated.h"

UENUM(BlueprintType)
enum class EZombieState : uint8 { Move, Attack, Damage, Die, };

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
	void AttackState();
	void DamageState();
	void DieState();

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class ADestinationActor_KJY* Target;

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class ACharacterBase_YMH* Player; // 추후 클래스 변경

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class AZombieBase_KJY* Me;
	
	UPROPERTY(EditAnywhere, Category=FSM)
	float MovetoPlayerRange = 100.0f;
	UPROPERTY(EditAnywhere, Category=FSM)
	float AttackRange = 30.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float CurrentTime = 0;
	
	UPROPERTY(EditAnywhere, Category=FSM)
	float AttackTime = 3.0f;
	
};
