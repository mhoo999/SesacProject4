// zombie must die


#include "Character/Player/PlayerUpgradeComp_YMH.h"

#include "EnhancedInputComponent.h"
#include "PlayerBase_YMH.h"
#include "PlayerBuildComp_LDJ.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/MoneyWidget_LDJ.h"
#include "UI/TrapAndWeaponLevelUI_LDJ.h"

UPlayerUpgradeComp_YMH::UPlayerUpgradeComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MouseModeRef(TEXT("/Game/LDJ/Input/IA_MouseMode.IA_MouseMode"));
	if (IA_MouseModeRef.Succeeded())
	{
		IA_MouseMode = IA_MouseModeRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LevelUpBtnRef(TEXT("/Game/LDJ/Input/IA_LevelUpBtn.IA_LevelUpBtn"));
	if (IA_LevelUpBtnRef.Succeeded())
	{
		IA_LevelUpBtn = IA_LevelUpBtnRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UTrapAndWeaponLevelUI_LDJ> LevelUpUIRef(TEXT("/Game/LDJ/UI/WBP_TrapLevel.WBP_TrapLevel_C"));
	if (LevelUpUIRef.Succeeded())
	{
		LevelUpUIFactory = LevelUpUIRef.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UMainUI_YMH> MainUIRef(TEXT("/Game/YMH/UI/WBP_MainUI_YMH.WBP_MainUI_YMH_C"));
	if (MainUIRef.Succeeded())
	{
		MainUIFactory = MainUIRef.Class;
	}
}

void UPlayerUpgradeComp_YMH::BeginPlay()
{
	Super::BeginPlay();
	LevelUpUI = Cast<UTrapAndWeaponLevelUI_LDJ>(CreateWidget(GetWorld(), LevelUpUIFactory));
}

void UPlayerUpgradeComp_YMH::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Trap Upgrade Input
		EnhancedInputComponent->BindAction(IA_MouseMode, ETriggerEvent::Started, this,
								   &UPlayerUpgradeComp_YMH::SetMouseMode);
		EnhancedInputComponent->BindAction(IA_LevelUpBtn, ETriggerEvent::Started, this,
		 				   &UPlayerUpgradeComp_YMH::LevelUp);
	}
}

void UPlayerUpgradeComp_YMH::SetMouseMode(const FInputActionValue& value)
{
	if (!bMouseMode)
	{
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetWorld()->GetFirstPlayerController());
		player->bIsReloading = true;
		player->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		player->CameraBoom->bUsePawnControlRotation = false;
		bMouseMode = true;
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
		player->bIsReloading = false;
		player->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		player->CameraBoom->bUsePawnControlRotation = true;
		bMouseMode = false;
	}
}

void UPlayerUpgradeComp_YMH::LevelUp(const FInputActionValue& value)
{
	if (GetWorld()->GetFirstPlayerController()->IsLocalController())
	{
		auto PC = GetWorld()->GetFirstPlayerController();
		auto Temp = Cast<APlayerController_YMH>(PC);
		auto MyPlayer  = Cast<APlayerBase_YMH>(Temp->GetPawn());
		MyPlayer->wallet+=100;
		Temp->mainUI->WBP_TrapLevel->LevelUpUI();
		Temp->mainUI->WBP_Money->SetMoneyText(MyPlayer->wallet);
	}
}