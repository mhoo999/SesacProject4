// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "HPWidget_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UHPWidget_KJY : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* HPText;
	
};
