// zombie must die


#include "Game/ZMDGameInstance_LDJ.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"

UZMDGameInstance_LDJ::UZMDGameInstance_LDJ()
{
}

void UZMDGameInstance_LDJ::Init()
{
	Super::Init();
	// ----- 온라인세션 인터페이스 만들기 -----
	auto Subsys = IOnlineSubsystem::Get();
	if (Subsys)
	{
		SessionInterface = Subsys->GetSessionInterface();
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UZMDGameInstance_LDJ::OnCreateSessionComplete); //세션이 만들어질 때 호출
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UZMDGameInstance_LDJ::OnFindSessionsComplete); //세션을 찾을 때 호출
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UZMDGameInstance_LDJ::OnJoinSessionCompleted); //방에 들어갔을 때, 호출
	}
	// ----- 온라인세션 인터페이스 만들기 -----
}

// ----- 2초후 세션 생성 타이머 -----
// FTimerHandle Handle;
// GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
// {
// 	CreateMySession(MySessionName, 2);
// }), 2 ,false);
// ----- 2초후 세션 생성 타이머 -----

void UZMDGameInstance_LDJ::CreateMySession(FString RoomName, int32 PlayerCount)
{
	// ----- 세션 설정 구조체 선언 -----
	FOnlineSessionSettings SessionSettings;// 세션 설정
	FName SubsysName = IOnlineSubsystem::Get()->GetSubsystemName();
	// ----- 세션 설정 구조체 선언 -----

	// ----- 세션 설정 Detail -----
	SessionSettings.bIsDedicated = false; //Dedicate Server 여부
	SessionSettings.bIsLANMatch = (SubsysName == "NULL"); //Default Engine.ini의 값 확인
	SessionSettings.bShouldAdvertise = true; //공개,비공개 여부 	--> /* SessionInterFace->SendSessionInviteToFriend() */
	SessionSettings.bUsesPresence = true; //온라인 상태 정보를 활용하게 할지 여부(게임중, 자리비움)
	SessionSettings.bAllowJoinInProgress = true; //게임중 접속 여부
	SessionSettings.bAllowJoinViaPresence = true; //게임중 접속 여부
	SessionSettings.NumPublicConnections = PlayerCount; //최대 허용 인원 수
	// ----- 세션 설정 Detail -----

	// ----- 세션 만들기 -----
	SessionSettings.Set(FName("Room_Name"), RoomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing); //커스텀 옵션(룸네임, 핑체크, 호스트이름)
	SessionSettings.Set(FName("Host_Name"), MySessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	FUniqueNetIdPtr NetID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId(); //세션 생성 후 특정 친구를 초대하거나, 보이스 챗을 해야 할 때 NetID가 있어야 하므로 NetID를 가져온다.
	SessionInterface->CreateSession(*NetID, FName(MySessionName), SessionSettings); //이 함수를 재귀하는 것이 아니라, 인터페이스에 있는 CreateSession함수를 가져오는 것
	// ----- 세션 만들기 -----
}

void UZMDGameInstance_LDJ::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Create Session Start : %s, %d"), *SessionName.ToString(), bWasSuccessful);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green,
		FString::Printf(TEXT("Create Session Start : %s, %d"), *SessionName.ToString(), bWasSuccessful));

	if (bWasSuccessful)
	{
		GetWorld()->ServerTravel(TEXT("/Game/KJY/Maps/ZombieMap1?listen"));// 서버가 방 안에 들어가도록 레벨을 열고 ?listen을 치자.
	}
}

void UZMDGameInstance_LDJ::FindOtherSession()
{
	// ----- 검색 조건 설정 -----
	SessionSearch = MakeShareable(new FOnlineSessionSearch); //언리얼 스마트포인터는 이렇게 인스턴스 생성을 한다.
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); //PRESENCE값이 True 인 것만 찾기
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";//LanMatching여부
	SessionSearch->MaxSearchResults = 10;//최대 찾는 세션 수
	// ----- 검색 조건 설정 -----
	
	// ----- 검색 실행 -----
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	OnSearchState.Broadcast(true);
	// ----- 검색 실행 -----
}

void UZMDGameInstance_LDJ::JoinSelectedSession(int32 RoomIndex)
{
	// ----- 여러 개의 방 목록 중 하나를 선택 -----
	auto sr = SessionSearch->SearchResults[RoomIndex]; // 여러개의 방 목록 중 하나를 선택
	SessionInterface->JoinSession(0, FName(MySessionName), sr); // 세션에 들어가는 함수.
	// ----- 여러 개의 방 목록 중 하나를 선택 -----
	
}

void UZMDGameInstance_LDJ::OnFindSessionsComplete(bool bWasSuccessful)
{
	// ----- 찾기 실패 시 -----
	if (bWasSuccessful == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("Session Search Failed..."));
		return;
	}
	// ----- 찾기 실패 시 -----

	// ----- 세션 검색 결과 데이터 -----
	const auto Results = SessionSearch->SearchResults;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("Search Result Count : %d"), Results.Num()));
	// ----- 세션 검색 결과 데이터 -----

	// ----- 세션 검색 정보 -----
	for (int i = 0; i < Results.Num();i++) //검색된 것들을 하나하나 정보 가져오기
	{
		auto sr = Results[i];
		if (sr.IsValid() == false) //유효하지 않으면 다음번으로 넘기기
		{
			continue;
		}
		
		// ----- 세션 검색된 정보 기입 -----
		FSessionInfo SessionInfo; // 효과적인 관리를 위한 구조체 선언 ZMDGameInstance.h 참고
		SessionInfo.Index = i; // 방 번호 기록
		sr.Session.SessionSettings.Get(FName("ROOM_NAME"), SessionInfo.RoomName); //방 이름
		FString OwnerName = sr.Session.OwningUserName; //PC소유자 이름
		sr.Session.SessionSettings.Get(FName("HOST_NAME"), SessionInfo.RoomName); //호스트 이름
		int32 MaxPlayerCount = sr.Session.SessionSettings.NumPublicConnections; //플레이어 수 : 최대 입장 수
		int32 CurrentPlayerCount = MaxPlayerCount - sr.Session.NumOpenPublicConnections; //플레이어 수 : 현재 입장 수
		SessionInfo.PlayerCount = FString::Printf(TEXT("(%d/%d)"), CurrentPlayerCount, MaxPlayerCount); //보기 좋게 포장해주기
		SessionInfo.PingSpeed = sr.PingInMs;//핑
		// ----- 세션 검색된 정보 기입 -----
		
		// ----- 완성된 세션 화면에 띄우기 -----
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, *SessionInfo.ToString()); //디버깅
		OnSearchCompleted.Broadcast(SessionInfo); //슬롯에 추가
		// ----- 완성된 세션 화면에 띄우기-----
	}
	OnSearchState.Broadcast(false);
	// ----- 세션 검색 정보 -----
	
}

void UZMDGameInstance_LDJ::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	// ----- 클라이언트 트래블 -----
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		FString URL;// 서버가 만든 세션의 URL이 필요함
		SessionInterface->GetResolvedConnectString(SessionName, URL); //세션이름으로부터 URL을 받는다.

		if (URL.IsEmpty() == false)
		{
			auto pc = GetWorld()->GetFirstPlayerController(); // 들어가자 방으로, 클라가 방으로 들어갈 때는 P.C가 있어야 한다.
			pc->ClientTravel(URL, TRAVEL_Absolute); // 들어가는 함수.
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Join Session Failed"));
	}
	// ----- 클라이언트 트래블 -----
}
