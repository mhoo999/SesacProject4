// zombie must die


#include "UI/TitleMenuUI_LDJ.h"

#include "StartMenuUI_LDJ.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


UTitleMenuUI_LDJ::UTitleMenuUI_LDJ(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UStartMenuUI_LDJ> StartMenuRef(TEXT("/Game/LDJ/UI/WBP_MainMenuReady_LDJ.WBP_MainMenuReady_LDJ_C"));
	if (StartMenuRef.Succeeded())
	{
		StartMenuFac = StartMenuRef.Class;
	}
}

void UTitleMenuUI_LDJ::NativeConstruct()
{
	Super::NativeConstruct();
	
	// ----- Delegate 선언 -----
	Btn_Start->OnClicked.AddDynamic(this,&UTitleMenuUI_LDJ::Click_Start);
	Btn_Start->OnHovered.AddDynamic(this,&UTitleMenuUI_LDJ::Hover_Start);
	Btn_Start->OnUnhovered.AddDynamic(this,&UTitleMenuUI_LDJ::UnHover_Start);
	Btn_Exit->OnClicked.AddDynamic(this,&UTitleMenuUI_LDJ::Click_Exit);
	Btn_Exit->OnHovered.AddDynamic(this,&UTitleMenuUI_LDJ::Hover_Exit);
	Btn_Exit->OnUnhovered.AddDynamic(this,&UTitleMenuUI_LDJ::UnHover_Exit);
	// ----- Delegate 선언 -----
}

void UTitleMenuUI_LDJ::Click_Start()
{
	UGameplayStatics::PlaySound2D(GetWorld(), click);
	StartMenu = Cast<UStartMenuUI_LDJ>(CreateWidget(GetWorld(), StartMenuFac));
	StartMenu->AddToViewport();
	StartMenu->ClickJoinSession();
}

void UTitleMenuUI_LDJ::Click_Exit()
{
	UGameplayStatics::PlaySound2D(GetWorld(), click);
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UTitleMenuUI_LDJ::Hover_Start()
{
	UGameplayStatics::PlaySound2D(GetWorld(), hover);
	Btn_Start->SetColorAndOpacity(FLinearColor::Gray);
}

void UTitleMenuUI_LDJ::UnHover_Start()
{
	Btn_Start->SetColorAndOpacity(FLinearColor::White);
}

void UTitleMenuUI_LDJ::Hover_Exit()
{
	UGameplayStatics::PlaySound2D(GetWorld(), hover);
	Btn_Exit->SetColorAndOpacity(FLinearColor::Gray);
}

void UTitleMenuUI_LDJ::UnHover_Exit()
{
	Btn_Exit->SetColorAndOpacity(FLinearColor::White);
}
