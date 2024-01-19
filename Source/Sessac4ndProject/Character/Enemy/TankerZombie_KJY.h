// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "TankerZombie_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API ATankerZombie_KJY : public AZombieBase_KJY
{
	GENERATED_BODY()

	ATankerZombie_KJY();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
};
