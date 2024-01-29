// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ZMDGameInstance_LDJ.generated.h"

USTRUCT(BlueprintType)
struct FSessionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString RoomName;
	UPROPERTY(BlueprintReadOnly)
	FString HostName;
	UPROPERTY(BlueprintReadOnly)
	FString PlayerCount;
	UPROPERTY(BlueprintReadOnly)
	int32 PingSpeed;
	UPROPERTY(BlueprintReadOnly)
	int32 Index;

	inline FString ToString()
	{
		return FString::Printf(TEXT("[%d] %s : %s - %s, %d ms"), Index, *RoomName, *HostName, *PlayerCount, PingSpeed);
	}
};

// ----- 세션 검색이 끝났을 때 호출되는 델리게이트 -----
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchSignature, const FSessionInfo&, SessionInfo); //블루프린트(Dynamic)와 브로드캐스팅(Multicast)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchStateSignature, bool, IsSearching); //블루프린트(Dynamic)와 브로드캐스팅(Multicast)

UCLASS()
class SESSAC4NDPROJECT_API UZMDGameInstance_LDJ : public UGameInstance
{
	GENERATED_BODY()
	UZMDGameInstance_LDJ();
public:
	// ----- override 함수 -----
	virtual void Init() override;
	// ----- override 함수 -----

	// ----- 함수 -----
	void CreateMySession(FString RoomName, int32 PlayerCount);//세션 생성함수
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);// 세션생성완료 이벤트 함수
	void FindOtherSession();// 세션 찾기
	void JoinSelectedSession(int32 RoomIndex); // 세션 입장함수
	
	UFUNCTION()
	void OnFindSessionsComplete(bool bWasSuccessful);
	
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	// ----- 함수 -----

	// ----- 참조 변수 -----
	// ----- 참조 변수 -----
	
	// ----- 변수 -----
	IOnlineSessionPtr SessionInterface; //세션 설정
	FString MySessionName = "Rooney"; //세션(호스트) 이름
	TSharedPtr<FOnlineSessionSearch> SessionSearch; //방검색 : UPROPERTY를 쓸 수 없는 Basic C++문법임
	FSearchSignature OnSearchCompleted; // 방 찾기 완료되면 콜백을 등록할 델리게이트
	FSearchStateSignature OnSearchState; // 방을 찾는 동안 '찾기' 버튼을 누르지 않도록 막아주는 변수 
	// ----- 변수 -----

	
};
