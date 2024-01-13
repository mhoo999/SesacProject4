// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI_YMH.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UMainUI_YMH : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category="UI", meta=(BindWidget))
	class UImage* img_cresshair;

	void ShowCrosshair(bool isShow);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HP")
	float hp = 1.0f;
};
