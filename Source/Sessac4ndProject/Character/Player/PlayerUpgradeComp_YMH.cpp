// zombie must die


#include "Character/Player/PlayerUpgradeComp_YMH.h"

#include "EnhancedInputComponent.h"
#include "PlayerBuildComp_LDJ.h"

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
}

void UPlayerUpgradeComp_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerUpgradeComp_YMH::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	// Trap Upgrade Input
	// EnhancedInputComponent->BindAction(IA_ChooseTrap1, ETriggerEvent::Triggered, this,
	// 						   &UPlayerBuildComp_LDJ::UpgradeSpikeTrap);
	// EnhancedInputComponent->BindAction(IA_MouseMode, ETriggerEvent::Started, this,
	// 						   &UPlayerBuildComp_LDJ::SetMouseMode);
	// EnhancedInputComponent->BindAction(IA_LevelUpBtn, ETriggerEvent::Started, this,
	// 				   &UPlayerBuildComp_LDJ::LevelUp);
}
