// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaveInformationUI_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UWaveInformationUI_LDJ : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Txt_WaveInfor;

	void SetWaveText(FText Description);
};
