// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_YMH.generated.h"

class UMainUI_YMH;
/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API APlayerController_YMH : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	// ------------------ main UI --------------------------
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMainUI_YMH> mainUIWidget;

	UPROPERTY()
	UMainUI_YMH* mainUI;
	
	void InitUIWidget();
};
