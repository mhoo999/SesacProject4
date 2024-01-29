// zombie must die


#include "UI/StartMenuUI_LDJ.h"

#include "SessionSlotWidget_LDJ.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Game/ZMDGameInstance_LDJ.h"
#include "Kismet/GameplayStatics.h"

void UStartMenuUI_LDJ::NativeConstruct()
{
	Super::NativeConstruct();
	// ----- 참조변수 초기화 -----
	GI = Cast<UZMDGameInstance_LDJ>(GetWorld()->GetGameInstance());
	// ----- 참조변수 초기화 -----
	
	// ----- 델리게이트 -----
	GI->OnSearchCompleted.AddDynamic(this, &UStartMenuUI_LDJ::AddSlotWidget);
	GI->OnSearchState.AddDynamic(this, &UStartMenuUI_LDJ::OnJoinButtonEnabled);
	Btn_CreateSession->OnClicked.AddDynamic(this, &UStartMenuUI_LDJ::ClickCreateSession);
	Btn_JoinSession->OnClicked.AddDynamic(this, &UStartMenuUI_LDJ::ClickJoinSession);
	Btn_Back->OnClicked.AddDynamic(this, &UStartMenuUI_LDJ::ClickBack);
	Btn_Play->OnClicked.AddDynamic(this, &UStartMenuUI_LDJ::ClickPlay);
	// ----- 델리게이트 -----
}

void UStartMenuUI_LDJ::ClickCreateSession()
{
	UGameplayStatics::PlaySound2D(GetWorld(), click);
	GI->CreateMySession(TEXT("TestGame"), 2);
}

void UStartMenuUI_LDJ::ClickJoinSession()
{
	UGameplayStatics::PlaySound2D(GetWorld(), click);
	ScrollBox_RoomList->ClearChildren();	
	if (GI)
	{
		GI->FindOtherSession();
	}
}

void UStartMenuUI_LDJ::ClickBack()
{
	UGameplayStatics::PlaySound2D(GetWorld(), click);
	RemoveFromParent();
}

void UStartMenuUI_LDJ::ClickPlay()
{
	UGameplayStatics::PlaySound2D(GetWorld(), click);
	UGameplayStatics::OpenLevel(GetWorld(), FName("ZombieMap1"));
}

void UStartMenuUI_LDJ::AddSlotWidget(const FSessionInfo& SessionInfo)
{
	// ----- 세션 스크롤박스에 위젯 추가하기 -----
	auto slot = CreateWidget<USessionSlotWidget_LDJ>(this, SessionSlotWidget); // 위젯 생성
	slot->Set(SessionInfo); // 데이터 할당
	ScrollBox_RoomList->AddChild(slot); // 스크롤박스에 띄우기
	// ----- 세션 스크롤박스에 위젯 추가하기 -----
}

void UStartMenuUI_LDJ::OnJoinButtonEnabled(bool bIsSearching)
{
	// ----- 세션을 찾는 동안에는 버튼 비활성화 -----
	Btn_JoinSession->SetIsEnabled(!bIsSearching);
	if (bIsSearching)
	{
		Txt_Finding->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Txt_Finding->SetVisibility(ESlateVisibility::Hidden);
	}
	// ----- 세션을 찾는 동안에는 버튼 비활성화 -----
}
