// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet_YMH.generated.h"

class UCapsuleComponent;
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	UCapsuleComponent* capsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	UMeshComponent* meshComp;
	
public:
	APlayerController_YMH* pc;

	UPROPERTY(EditAnywhere, Category="MySettings")
	float destroyTime = 5.0f;
	UPROPERTY(EditAnywhere, Category="MySettings")
	float bulletSpeed = 5000.0f;
	
	FVector destination;
	FVector direction;
};
