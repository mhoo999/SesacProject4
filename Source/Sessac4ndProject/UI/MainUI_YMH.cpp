// zombie must die


#include "UI/MainUI_YMH.h"

#include "Components/Image.h"

void UMainUI_YMH::ShowPointer()
{
	img_pointer->SetVisibility(ESlateVisibility::Visible);
}

void UMainUI_YMH::ShowCrosshair(bool isShow)
{
	if (isShow)
	{
		img_cresshair->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		img_cresshair->SetVisibility(ESlateVisibility::Hidden);
	}
}
