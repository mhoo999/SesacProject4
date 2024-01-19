// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MainUI_YMH.generated.h"

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
	void ShowCrosshair(bool isShow);
	FVector2D LerpSize;
	FTimerHandle restoreHandle;

	FVector2D crosshairSize = FVector2D(1);
	void restoreCrosshair();
	
public:
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	UUniformGridPanel* BulletPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Bullet")
	TSubclassOf<UUserWidget> BulletUIFactory;

	// 총알 위젯 추가
	void AddBullet();
	// 총알 제거
	void PopBullet(int32 index);
	// 모든 총알 UI 제거
	void RemoveAllAmmo();

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
};
