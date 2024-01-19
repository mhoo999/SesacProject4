// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase_YMH.h"
#include "InputActionValue.h"
#include "PlayerBase_YMH.generated.h"

class UPointLightComponent;
class UMainUI_YMH;
class APlayerController_YMH;
class UPlayerBuildComp_LDJ;
class UPlayerFireComp_YMH;
class UPlayerMoveComp_YMH;
class UPlayerBaseComp_YMH;
struct FInputActionValue;
class UInputAction;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FInputDelegate, UInputComponent*);

UCLASS()
class SESSAC4NDPROJECT_API APlayerBase_YMH : public ACharacterBase_YMH
{
	GENERATED_BODY()

public:
	APlayerBase_YMH();

public:
	FInputDelegate OnSetupInputDelegate;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	USpringArmComponent* SelfCameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	USceneCaptureComponent2D* SelfCapture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|COmponents")
	UPointLightComponent* PointLightComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UPlayerMoveComp_YMH* MoveComp;

	UPROPERTY(EditDefaultsOnly)
	UPlayerFireComp_YMH* FireComp;

	UPROPERTY(EditDefaultsOnly)
	UPlayerBuildComp_LDJ* BuildComp;
	
	// 무기 레벨
	int32 weaponeGrade;

	// 재화
	UPROPERTY()
	int32 wallet;

	// 교전 여부
	bool bIsCombat = false;
	// 재장전 여부
	bool bIsReloading = false;
	// 빌드 모드 여부
	bool bIsBuildMode = false;
	// 반동 크기
	float MaxRecoilValue;
	float MinRecoilValue;
	float crosshairRecoilValue;
	// 공격 대기 상태 여부
	bool fireDispatcher = false;
	
public:
	// --------------- 플레이어 체력 --------------------
	virtual void BeShot(float damage) override;
	void DieProcess();

public:
	// --------------- 플레이어 BulletCount --------------------
	int32 MaxBulletCount;
	int32 reloadBulletCount;
	UPROPERTY()
	int32 bulletCount;

public:
	UPROPERTY()
	APlayerController_YMH* playerController;
};

