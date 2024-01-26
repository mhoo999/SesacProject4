// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeComp_YMH.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UUpgradeComp_YMH : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUpgradeComp_YMH();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

private:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_MouseMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_LevelUpBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_WaveStart;*/

public:
	
};
