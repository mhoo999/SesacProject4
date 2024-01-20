// zombie must die


#include "UI/MainUI_YMH.h"

#include "FrameTypes.h"
#include "GPUMessaging.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"

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

void UMainUI_YMH::restoreCrosshair()
{
	LerpSize =	FMath::Lerp(LerpSize, FVector2D(1.0, 1.0), GetWorld()->GetDeltaSeconds() * 4);
	img_cresshair->SetRenderScale(LerpSize);
	if (LerpSize == FVector2D(1.0))
	{
		GetWorld()->GetTimerManager().ClearTimer(restoreHandle);
	}
}

void UMainUI_YMH::SelectSlot(int32 num)
{
	switch (num)
	{
	case 0:
		AbleSlot(slot0, img_slot0);
		DisableSlot(slot1, img_slot1);
		DisableSlot(slot2, img_slot2);
		DisableSlot(slot3, img_slot3);
		DisableSlot(slot4, img_slot4);
		break;
	case 1:
		DisableSlot(slot0, img_slot0);
		AbleSlot(slot1, img_slot1);
		DisableSlot(slot2, img_slot2);
		DisableSlot(slot3, img_slot3);
		DisableSlot(slot4, img_slot4);
		break;
	case 2:
		DisableSlot(slot0, img_slot0);
		DisableSlot(slot1, img_slot1);
		AbleSlot(slot2, img_slot2);
		DisableSlot(slot3, img_slot3);
		DisableSlot(slot4, img_slot4);
		break;
	case 3:
		DisableSlot(slot0, img_slot0);
		DisableSlot(slot1, img_slot1);
		DisableSlot(slot2, img_slot2);
		AbleSlot(slot3, img_slot3);
		DisableSlot(slot4, img_slot4);
		break;
	case 4:
		DisableSlot(slot0, img_slot0);
		DisableSlot(slot1, img_slot1);
		DisableSlot(slot2, img_slot2);
		DisableSlot(slot3, img_slot3);
		AbleSlot(slot4, img_slot4);
		break;
	}
}

void UMainUI_YMH::AbleSlot(UBorder* slot, UImage* img)
{
	slot->SetBrushColor(FColor::Blue);
	img->SetOpacity(2.0f);
}

void UMainUI_YMH::DisableSlot(UBorder* slot, UImage* img)
{
	slot->SetBrushColor(FColor::White);
	img->SetOpacity(0.8f);
}

void UMainUI_YMH::weaponRecoil()
{
	img_cresshair->SetRenderScale(FVector2D(3.0));
	LerpSize = FVector2D(3.0, 3.0);
	
	GetWorld()->GetTimerManager().ClearTimer(restoreHandle);
	GetWorld()->GetTimerManager().SetTimer(restoreHandle, FTimerDelegate::CreateLambda([&]
	{
		restoreCrosshair();
	}), GetWorld()->GetDeltaSeconds(), true, 1.5);
}
