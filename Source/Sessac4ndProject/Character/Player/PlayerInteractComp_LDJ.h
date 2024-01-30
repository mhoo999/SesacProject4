// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractComp_LDJ.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UPlayerInteractComp_LDJ : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerInteractComp_LDJ();

	// ----- override 함수 -----
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ----- override 함수 -----

	// ----- 함수 -----
	void InteractLineTrace();

	void BringZombieHPAndShowUI(AActor* HitActor);

	UFUNCTION(Client, UnReliable)
	void ClientRPC_InteractionTrace(AZombieBase_KJY* HitActor);
	// ----- 함수 -----

	// ----- 변수 -----
	UPROPERTY()
	class APlayerBase_YMH* Player;
	
	UPROPERTY()
	class APlayerController* PC;

	UPROPERTY()
	class APlayerController_YMH* MyPC;

	FCollisionQueryParams params;

	FVector StartVec;
	FVector EndVec;

	UPROPERTY()
	TArray<AActor*> ToIgnore;
	// ----- 변수 -----
	UFUNCTION(Server, UnReliable)
	void ServerRPC_InteractionTrace(FHitResult HitInfo22);
	
};
