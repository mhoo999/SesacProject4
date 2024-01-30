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
	class UBoxComponent* collisionComp;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class APlayerBase_YMH* Player; 
	
	UFUNCTION()
	virtual void OnBeginItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							  const FHitResult& SweepResult);

	virtual void ReactItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* SkillUpItemDropSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* SkillUpItemEatSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* GoldItemDropSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* HealthPosionDropSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* HealthPosionEatSound;
};
