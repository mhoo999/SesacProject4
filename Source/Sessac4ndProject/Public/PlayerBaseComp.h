// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseComp.generated.h"


class APlayerBase_YMH;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UPlayerBaseComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerBaseComp();

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent);

public:
	UPROPERTY()
	APlayerBase_YMH* player;
};
