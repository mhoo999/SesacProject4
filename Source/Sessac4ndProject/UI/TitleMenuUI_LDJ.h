// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleMenuUI_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UTitleMenuUI_LDJ : public UUserWidget
{
	GENERATED_BODY()
	UTitleMenuUI_LDJ(const FObjectInitializer& ObjectInitializer);
	
public:
	// ----- Override 함수 -----
	virtual void NativeConstruct() override;
	// ----- Override 함수 -----

	// ----- 함수 -----
	UFUNCTION()
	void Click_Start();
	
	UFUNCTION()
	void Click_Exit();

	UFUNCTION()
	void Hover_Start();

	UFUNCTION()
	void UnHover_Start();

	UFUNCTION()
	void Hover_Exit();

	UFUNCTION()
	void UnHover_Exit();
	// ----- 함수 -----

	// ----- 참조 변수 -----
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UStartMenuUI_LDJ> StartMenuFac;

	UPROPERTY()
	class UStartMenuUI_LDJ* StartMenu;
	// ----- 참조 변수 -----

	// ----- 변수 -----
	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_Start;

	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_Exit;
	// ----- 변수 -----

	UPROPERTY(EditAnywhere)
	USoundBase* hover;

	UPROPERTY(EditAnywhere)
	USoundBase* click;
};
