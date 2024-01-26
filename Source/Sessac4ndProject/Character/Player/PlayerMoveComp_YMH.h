// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComp_YMH.h"
#include "InputActionValue.h"
#include "PlayerMoveComp_YMH.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UPlayerMoveComp_YMH : public UPlayerBaseComp_YMH
{
	GENERATED_BODY()

public:
	UPlayerMoveComp_YMH();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_Walk;

public:
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Jump(const FInputActionValue& value);
	void OnStartWalk(const FInputActionValue& value);
	void OnEndWalk(const FInputActionValue& value);
	
};
