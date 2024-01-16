// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MainUI_YMH.generated.h"

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
	void weaponRecoil(float value);
};
