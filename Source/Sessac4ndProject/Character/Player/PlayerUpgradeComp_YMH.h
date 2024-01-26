// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/PlayerBaseComp_YMH.h"
#include "PlayerUpgradeComp_YMH.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UPlayerUpgradeComp_YMH : public UPlayerBaseComp_YMH
{
	GENERATED_BODY()

public:
	UPlayerUpgradeComp_YMH();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

public:
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	// UInputAction* IA_MouseMode;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	// UInputAction* IA_LevelUpBtn;
	//
	// bool bMouseMode = false;
};
