// zombie must die


#include "UI/SessionSlotWidget_LDJ.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Game/ZMDGameInstance_LDJ.h"

void USessionSlotWidget_LDJ::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Join->OnClicked.AddDynamic(this, &USessionSlotWidget_LDJ::JoinSession);
}

void USessionSlotWidget_LDJ::JoinSession()
{
	auto GI = Cast<UZMDGameInstance_LDJ>(GetWorld()->GetGameInstance());

	if (GI)
	{
		GI->JoinSelectedSession(SessionNumber);
	}
}

void USessionSlotWidget_LDJ::Set(const FSessionInfo& SessionInfo)
{
	// 세션(방)번호
	Txt_SessionNumber->SetText(FText::FromString(FString::Printf(TEXT("[%d]"), SessionInfo.Index)));
	// 방이름
	Txt_RoomName->SetText(FText::FromString(SessionInfo.RoomName));
	// 방장이름
	Txt_HostName->SetText(FText::FromString(SessionInfo.HostName));
	Txt_PlayerCount->SetText(FText::FromString(SessionInfo.PlayerCount));
	// 핑
	Txt_PingSpeed->SetText(FText::FromString(FString::Printf(TEXT("%d ms"), SessionInfo.PingSpeed)));
	SessionNumber = SessionInfo.Index;
}
