// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RemainZombieUI_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API URemainZombieUI_LDJ : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Txt_RemainZombie;

	void SetRemainZombie(int32 RemainZombies);
};
