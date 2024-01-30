// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet_YMH.generated.h"

class APlayerBase_YMH;
class UBoxComponent;
class APlayerController_YMH;

UCLASS()
class SESSAC4NDPROJECT_API ABullet_YMH : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet_YMH();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	UBoxComponent* capsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	UStaticMeshComponent* meshComp;
	
public:
	APlayerController_YMH* pc;

	UPROPERTY(EditAnywhere, Category="MySettings")
	float destroyTime = 3.0f;
	UPROPERTY(EditAnywhere, Category="MySettings")
	float bulletSpeed = 5000.0f;
	
	FVector destination;
	FVector direction;

	// APlayerBase_YMH* Owner = nullptr;
	// void FindOwner();
};
