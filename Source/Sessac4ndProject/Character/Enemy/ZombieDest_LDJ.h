// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieDest_LDJ.generated.h"

UCLASS()
class SESSAC4NDPROJECT_API AZombieDest_LDJ : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieDest_LDJ();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LDJSettings")
	class UStaticMeshComponent* BodyComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LDJSettings")
	class UBoxComponent* BoxComp;

	UPROPERTY()
	class AZMDGameStateBase_LDJ* GameState;

	// TO DO : 좀비 포인터 레퍼 넣기
	UFUNCTION()
	void OnZombieOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
