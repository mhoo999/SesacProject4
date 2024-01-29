// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor_KJY.generated.h"

UCLASS()
class SESSAC4NDPROJECT_API AItemActor_KJY : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor_KJY();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* collisionComp;

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class APlayerBase_YMH* Player; 
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							  const FHitResult& SweepResult);
};
