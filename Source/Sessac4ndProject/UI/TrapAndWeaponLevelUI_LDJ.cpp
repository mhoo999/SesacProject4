// zombie must die


#include "UI/TrapAndWeaponLevelUI_LDJ.h"

#include "Character/Player/PlayerBase_YMH.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTrapAndWeaponLevelUI_LDJ::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_WeaponUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::WeaponLevelUp);
	Btn_SpikeTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::SpikeTrapLevelUp);
	Btn_FreezeTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::FreezeTrapLevelUp);
	Btn_PoisonTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::PoisonTrapLevelUp);
	Btn_FlameTrapUpgrade->OnClicked.AddDynamic(this, &UTrapAndWeaponLevelUI_LDJ::FlameTrapLevelUp);
	MyPlayer = Cast<APlayerBase_YMH>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	BuildComp = MyPlayer->FindComponentByClass<UPlayerBuildComp_LDJ>();
}

void UTrapAndWeaponLevelUI_LDJ::WeaponLevelUp()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST1"));
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::SpikeTrapLevelUp()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST2"));
	BuildComp->SpikeTrapLevel++;
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::FreezeTrapLevelUp()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST3"));
	BuildComp->FreezeTrapLevel++;
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::PoisonTrapLevelUp()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST4"));
	BuildComp->PoisonTrapLevel++;
	RefreshLevelupUI();
}

void UTrapAndWeaponLevelUI_LDJ::FlameTrapLevelUp()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST5"));
	BuildComp->FlameTrapLevel++;
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
	Btn_WeaponUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_SpikeTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_FreezeTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_PoisonTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Btn_FlameTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
	Txt_SpikeTrapLevel->SetText(FText::AsNumber(BuildComp->SpikeTrapLevel));
	Txt_FreezeTrapLevel->SetText(FText::AsNumber(BuildComp->FreezeTrapLevel));
	Txt_PoisonTrapLevel->SetText(FText::AsNumber(BuildComp->PoisonTrapLevel));
	Txt_FlameTrapLevel->SetText(FText::AsNumber(BuildComp->FlameTrapLevel));
}
