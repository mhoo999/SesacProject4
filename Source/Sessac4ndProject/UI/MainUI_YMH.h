// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MainUI_YMH.generated.h"

class UTextBlock;
class UUniformGridPanel;
class UBorder;
class UImage;

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UMainUI_YMH : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	UImage* img_pointer;
	void ShowPointer();
	
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	UImage* img_cresshair;
	void ShowCrosshair();
	FVector2D LerpSize;
	FTimerHandle restoreHandle;

	FVector2D crosshairSize = FVector2D(1);
	void restoreCrosshair();
	
public:
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	UTextBlock* CurrentBullet;

	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	UTextBlock* MaxBullet;

public:
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	UBorder* CharacterFrame;

public:
	// ------------------ Skill Slot ------------------------

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UBorder* slot0;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UBorder* slot1;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UBorder* slot2;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UBorder* slot3;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UBorder* slot4;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UImage* img_slot0;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UImage* img_slot1;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UImage* img_slot2;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UImage* img_slot3;

	UPROPERTY(BlueprintReadWrite, Category="Slot", meta=(BindWidget))
	UImage* img_slot4;

	void SelectSlot(int32 num);
	void AbleSlot(UBorder* slot, UImage* img);
	void DisableSlot(UBorder* slot, UImage* img);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HP")
	float hp = 1.0f;

public:
	void weaponRecoil();

	// ------------------------ wave info -----------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Txt_WaveInfor;

	void SetWaveText(FText Description);

	// --------------------- Trap & Weapon upgrade --------------------
	virtual void NativeConstruct() override;
	// 함정,웨폰 레벨은 플레이어에서 관리해서 넣기?
	UPROPERTY()
	class APlayerBase_YMH* MyPlayer;

	UPROPERTY(EditAnywhere)
	class UPlayerBuildComp_LDJ* BuildComp;

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