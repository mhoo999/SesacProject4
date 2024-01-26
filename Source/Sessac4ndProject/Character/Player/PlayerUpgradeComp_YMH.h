// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/PlayerBaseComp_YMH.h"
#include "PlayerUpgradeComp_YMH.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UPlayerUpgradeComp_YMH : public UPlayerBaseComp_YMH
{
	GENERATED_BODY()

public:
	// ----- 상속 함수 -----
	UPlayerUpgradeComp_YMH();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

	// ----- 동작 함수 -----
	void SetMouseMode(const FInputActionValue& value);
	void LevelUp(const FInputActionValue& value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	class UInputAction* IA_MouseMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	class UInputAction* IA_LevelUpBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TrapLevel")
	int32 SpikeTrapLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TrapLevel")
	int32 FreezeTrapLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TrapLevel")
	int32 PoisonTrapLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TrapLevel")
	int32 FlameTrapLevel = 1;
	
	bool bMouseMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIWidget")
	TSubclassOf<class UTrapAndWeaponLevelUI_LDJ> LevelUpUIFactory;
	
	UPROPERTY()
	class UTrapAndWeaponLevelUI_LDJ* LevelUpUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIWidget")
	TSubclassOf<class UMainUI_YMH> MainUIFactory;

	UPROPERTY()
	class UMainUI_YMH* MainUI;
};


// 1. 블루프린트에서 컴포넌트 붙여넣기
// 2.
