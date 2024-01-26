// zombie must die


#include "UI/MainUI_YMH.h"

#include "FrameTypes.h"
#include "GPUMessaging.h"
#include "TrapAndWeaponLevelUI_LDJ.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"

void UMainUI_YMH::ShowPointer()
{
	img_pointer->SetVisibility(ESlateVisibility::Visible);
}

void UMainUI_YMH::ShowCrosshair()
{
	img_cresshair->SetVisibility(ESlateVisibility::Visible);
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
//
// void UMainUI_YMH::SetWaveText(FText Description)
// {
// 	Txt_WaveInfor->SetText(Description);
// }
//
// void UMainUI_YMH::NativeConstruct()
// {
// 	Super::NativeConstruct();
// 	Btn_WeaponUpgrade->OnClicked.AddDynamic(this, &UMainUI_YMH::WeaponLevelUp);
// 	Btn_SpikeTrapUpgrade->OnClicked.AddDynamic(this, &UMainUI_YMH::SpikeTrapLevelUp);
// 	Btn_FreezeTrapUpgrade->OnClicked.AddDynamic(this, &UMainUI_YMH::FreezeTrapLevelUp);
// 	Btn_PoisonTrapUpgrade->OnClicked.AddDynamic(this, &UMainUI_YMH::PoisonTrapLevelUp);
// 	Btn_FlameTrapUpgrade->OnClicked.AddDynamic(this, &UMainUI_YMH::FlameTrapLevelUp);
// 	MyPlayer = Cast<APlayerBase_YMH>(GetWorld()->GetFirstPlayerController()->GetCharacter());
// 	BuildComp = MyPlayer->FindComponentByClass<UPlayerBuildComp_LDJ>();
// }
//
// void UMainUI_YMH::WeaponLevelUp()
// {
// 	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST1"));
// 	RefreshLevelupUI();
// }
//
// void UMainUI_YMH::SpikeTrapLevelUp()
// {
// 	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST2"));
// 	BuildComp->SpikeTrapLevel++;
// 	RefreshLevelupUI();
// }
//
// void UMainUI_YMH::FreezeTrapLevelUp()
// {
// 	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST3"));
// 	BuildComp->FreezeTrapLevel++;
// 	RefreshLevelupUI();
// }
//
// void UMainUI_YMH::PoisonTrapLevelUp()
// {
// 	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST4"));
// 	BuildComp->PoisonTrapLevel++;
// 	RefreshLevelupUI();
// }
//
// void UMainUI_YMH::FlameTrapLevelUp()
// {
// 	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("TEST5"));
// 	BuildComp->FlameTrapLevel++;
// 	RefreshLevelupUI();
// }
//
// void UMainUI_YMH::LevelUpUI()
// {
// 	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("Visible"));
// 	Btn_WeaponUpgrade->SetVisibility(ESlateVisibility::Visible);
// 	Btn_SpikeTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
// 	Btn_FreezeTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
// 	Btn_PoisonTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
// 	Btn_FlameTrapUpgrade->SetVisibility(ESlateVisibility::Visible);
// }
//
// void UMainUI_YMH::RefreshLevelupUI()
// {
// 	Btn_WeaponUpgrade->SetVisibility(ESlateVisibility::Hidden);
// 	Btn_SpikeTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
// 	Btn_FreezeTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
// 	Btn_PoisonTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
// 	Btn_FlameTrapUpgrade->SetVisibility(ESlateVisibility::Hidden);
// 	Txt_SpikeTrapLevel->SetText(FText::AsNumber(BuildComp->SpikeTrapLevel));
// 	Txt_FreezeTrapLevel->SetText(FText::AsNumber(BuildComp->FreezeTrapLevel));
// 	Txt_PoisonTrapLevel->SetText(FText::AsNumber(BuildComp->PoisonTrapLevel));
// 	Txt_FlameTrapLevel->SetText(FText::AsNumber(BuildComp->FlameTrapLevel));
// }