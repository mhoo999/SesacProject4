// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "ZombieHPUI_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UZombieHPUI_LDJ : public UUserWidget
{
	GENERATED_BODY()
public:
	// ----- override 함수 -----
	// ----- override 함수 -----

	// ----- 함수 -----
		
	void ShowZombieHPUI(float CurrentHP, float MaxHP,AZombieBase_KJY* Enemy);
	void ClearZombieHPUI();
	// ----- 함수 -----

	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UBorder* Border_ZombieHPUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Txt_ZombieInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* ProgBar_ZombieHP;

	float Percent;
	// ----- 변수 -----
};
