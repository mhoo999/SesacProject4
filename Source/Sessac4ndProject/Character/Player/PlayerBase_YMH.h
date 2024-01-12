// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase_YMH.h"
#include "InputActionValue.h"
#include "PlayerBase_YMH.generated.h"

class UPlayerFireComp;
class UPlayerMoveComp_YMH;
class UPlayerBaseComp;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	UPlayerMoveComp_YMH* MoveComp;

	UPROPERTY(EditDefaultsOnly)
	UPlayerFireComp* FireComp;
	
	// 탄창
	UPROPERTY()
	int32 bulletCount;
	
	// 공격 속도
	float fireSpeed;
	
	// 무기 레벨
	int32 weaponeGrade;

	// 재화
	UPROPERTY()
	int32 wallet;
	
public:
	// 트랩 설치
	void InstallTrap();
	
	// 무기, 트랩 선택
	void Selector();
};

