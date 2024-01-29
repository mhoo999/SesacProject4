// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuUI_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UStartMenuUI_LDJ : public UUserWidget
{
	GENERATED_BODY()
public:
	// ----- Override 함수 -----
	virtual void NativeConstruct() override;
	// ----- Override 함수 -----

	// ----- 함수 -----
	UFUNCTION()
	void ClickCreateSession();

	UFUNCTION()
	void ClickJoinSession();
	
	UFUNCTION()
	void ClickBack();
	
	UFUNCTION()
	void ClickPlay();
	
	UFUNCTION()
	void AddSlotWidget(const struct FSessionInfo& SessionInfo);
	
	UFUNCTION()
	void OnJoinButtonEnabled(bool bIsSearching);
	// ----- 함수 -----

	// ----- 참조 변수 -----
	UPROPERTY()
	class UZMDGameInstance_LDJ* GI;
	// ----- 참조 변수 -----

	// ----- 변수 -----
	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_CreateSession;

	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_JoinSession;

	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_Back;

	UPROPERTY(meta=(BindWidget))
	class UButton* Btn_Play;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	class UScrollBox* ScrollBox_RoomList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	class UScrollBox* ScrollBox_CharacterList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USessionSlotWidget_LDJ> SessionSlotWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Txt_Finding;
	// ----- 변수 -----
	
	UPROPERTY(EditAnywhere)
	USoundBase* click;
};
