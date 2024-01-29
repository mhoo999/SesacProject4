// zombie must die


#include "UI/ZombieHPUI_LDJ.h"

#include "Components/Border.h"
#include "Components/ProgressBar.h"

void UZombieHPUI_LDJ::ShowZombieHPUI(float CurrentHP, float MaxHP)
{
	Percent = CurrentHP/MaxHP;
	ProgBar_ZombieHP->SetPercent(Percent);
	Border_ZombieHPUI->SetVisibility(ESlateVisibility::Visible);
}

void UZombieHPUI_LDJ::ClearZombieHPUI()
{
	Border_ZombieHPUI->SetVisibility(ESlateVisibility::Hidden);
}
