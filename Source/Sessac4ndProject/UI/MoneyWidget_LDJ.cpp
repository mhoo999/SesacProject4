// zombie must die


#include "UI/MoneyWidget_LDJ.h"

#include "Components/TextBlock.h"

void UMoneyWidget_LDJ::SetMoneyText(int32 Wallet)
{
	Txt_MyMoney->SetText(FText().AsNumber(Wallet));
}
