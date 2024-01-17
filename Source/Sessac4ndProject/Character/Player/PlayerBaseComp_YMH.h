// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseComp_YMH.generated.h"


class APlayerController_YMH;
class UMainUI_YMH;
class APlayerBase_YMH;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UPlayerBaseComp_YMH : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerBaseComp_YMH();

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent);

public:
	UPROPERTY()
	APlayerBase_YMH* player;

	UPROPERTY()
	APlayerController_YMH* PlayerController;
};
