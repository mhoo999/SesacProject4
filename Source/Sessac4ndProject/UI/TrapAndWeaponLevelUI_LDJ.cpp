// zombie must die


#include "UI/TrapAndWeaponLevelUI_LDJ.h"

#include "Character/Player/PlayerBase_YMH.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Character/Player/PlayerFireComp_YMH.h"
#include "Character/Player/PlayerUpgradeComp_YMH.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Trap/FlameThrowerTrap_LDJ.h"
#include "Trap/FreezeTrap_LDJ.h"
#include "Trap/PoisonTrap_LDJ.h"
#include "Trap/SpikeTrap_LDJ.h"
#include "Trap/TrapBase.h"

void UTrapAndWeaponLevelUI_LDJ::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_WeaponUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::WeaponLevelUp);
	Btn_SpikeTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::SpikeTrapLevelUp);
	Btn_FreezeTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::FreezeTrapLevelUp);
	Btn_PoisonTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::PoisonTrapLevelUp);
	Btn_FlameTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::FlameTrapLevelUp);
	MyPlayer = Cast<APlayerBase_YMH>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	UpgradeComp = MyPlayer->FindComponentByClass<UPlayerUpgradeComp_YMH>();
	BuildComp = MyPlayer->FindComponentByClass<UPlayerBuildComp_LDJ>();
	FireComp = MyPlayer->FindComponentByClass<UPlayerFireComp_YMH>();
}

void UTrapAndWeaponLevelUI_LDJ::WeaponLevelUp()
{
	FireComp->weaponeUpgrade();
	MyPlayer->skillPoint--;
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::SpikeTrapLevelUp()
{
	UpgradeComp->SpikeTrapLevel++;
	auto CurrentTrap = Cast<ASpikeTrap_LDJ>(BuildComp->SelectedTrap);
	if (CurrentTrap)
	{
		BuildComp->SelectedTrap->Cost += 25;
	}
	MyPlayer->skillPoint--;
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::FreezeTrapLevelUp()
{
	UpgradeComp->FreezeTrapLevel++;
	auto CurrentTrap = Cast<AFreezeTrap_LDJ>(BuildComp->SelectedTrap);
	if (CurrentTrap)
	{
		BuildComp->SelectedTrap->Cost += 25;
	}
	MyPlayer->skillPoint--;
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::PoisonTrapLevelUp()
{
	UpgradeComp->PoisonTrapLevel++;
	auto CurrentTrap = Cast<APoisonTrap_LDJ>(BuildComp->SelectedTrap);
	if (CurrentTrap)
	{
		BuildComp->SelectedTrap->Cost += 25;
	}
	MyPlayer->skillPoint--;
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::FlameTrapLevelUp()
{
	UpgradeComp->FlameTrapLevel++;
	auto CurrentTrap = Cast<AFlameThrowerTrap_LDJ>(BuildComp->SelectedTrap);
	if (CurrentTrap)
	{
		BuildComp->SelectedTrap->Cost += 25;
	}
	MyPlayer->skillPoint--;
	RefreshLevelupUI();
	
}

void UTrapAndWeaponLevelUI_LDJ::LevelUpUI()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("Visible"));
	Btn_WeaponUpgrade->SetVisibility(ESlateVisibility::Visible);
	Btn_SpikeTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
	Btn_FreezeTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
	Btn_PoisonTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
	Btn_FlameTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
}

void UTrapAndWeaponLevelUI_LDJ::RefreshLevelupUI()
{
	GEngine->AddOnScreenDebugMessage(1,3,FColor::Red, FString::Printf(TEXT("%d"), MyPlayer->skillPoint));
	Btn_WeaponUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_SpikeTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_FreezeTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_PoisonTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_FlameTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Txt_WeaponLevel->SetText(FText::AsNumber(FireComp->Damage));
	Txt_SpikeTrapLevel->SetText(FText::AsNumber(UpgradeComp->SpikeTrapLevel));
	Txt_FreezeTrapLevel->SetText(FText::AsNumber(UpgradeComp->FreezeTrapLevel));
	Txt_PoisonTrapLevel->SetText(FText::AsNumber(UpgradeComp->PoisonTrapLevel));
	Txt_FlameTrapLevel->SetText(FText::AsNumber(UpgradeComp->FlameTrapLevel));
	
	if (MyPlayer->skillPoint >= 0)
	{
		LevelUpUI();
	}
}
