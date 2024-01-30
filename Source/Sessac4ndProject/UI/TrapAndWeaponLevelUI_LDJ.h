// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrapAndWeaponLevelUI_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UTrapAndWeaponLevelUI_LDJ : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	// 함정,웨폰 레벨은 플레이어에서 관리해서 넣기?
	UPROPERTY()
	class APlayerBase_YMH* MyPlayer;

	UPROPERTY(EditAnywhere)
	class UPlayerUpgradeComp_YMH* UpgradeComp;

	UPROPERTY(EditAnywhere)
	class UPlayerBuildComp_LDJ* BuildComp;

	UPROPERTY(EditAnywhere)
	class UPlayerFireComp_YMH* FireComp;

public:
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UButton* Btn_WeaponUpgrade;
	UFUNCTION()
	void WeaponLevelUp();

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UButton* Btn_SpikeTrapUpgrade;
	UFUNCTION()
	void SpikeTrapLevelUp();

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UButton* Btn_FreezeTrapUpgrade;
	UFUNCTION()
	void FreezeTrapLevelUp();

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UButton* Btn_PoisonTrapUpgrade;
	UFUNCTION()
	void PoisonTrapLevelUp();

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UButton* Btn_FlameTrapUpgrade;
	UFUNCTION()
	void FlameTrapLevelUp();
	
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UTextBlock* Txt_WeaponLevel;

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UTextBlock* Txt_SpikeTrapLevel;

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UTextBlock* Txt_FreezeTrapLevel;

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UTextBlock* Txt_PoisonTrapLevel;

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UTextBlock* Txt_FlameTrapLevel;
	
	void LevelUpUI();
	void RefreshLevelupUI();
};
