// zombie must die


#include "UI/ZombieHPUI_LDJ.h"

#include "Character/Enemy/FastZombie_KJY.h"
#include "Character/Enemy/TankerZombie_KJY.h"
#include "Character/Enemy/Zombie_KJY.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UZombieHPUI_LDJ::ShowZombieHPUI(float CurrentHP, float MaxHP,AZombieBase_KJY* Enemy)
{
	Percent = CurrentHP/MaxHP;
	ProgBar_ZombieHP->SetPercent(Percent);
	auto CastNormal = Cast<AZombie_KJY>(Enemy);
	auto CastTanker = Cast<ATankerZombie_KJY>(Enemy);
	auto CastFaster = Cast<AFastZombie_KJY>(Enemy);
	if (CastNormal)
	{
		Txt_ZombieInfo->SetText(FText::FromString(TEXT("Zombie")));
	}
	if (CastTanker)
	{
		Txt_ZombieInfo->SetText(FText::FromString(TEXT("Tanker")));
	}
	if (CastFaster)
	{
		Txt_ZombieInfo->SetText(FText::FromString(TEXT("Faster")));
	}
	Border_ZombieHPUI->SetVisibility(ESlateVisibility::Visible);
}

void UZombieHPUI_LDJ::ClearZombieHPUI()
{
	Border_ZombieHPUI->SetVisibility(ESlateVisibility::Hidden);
}
