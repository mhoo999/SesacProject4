// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "ZombieBase_KJY.h"
#include "Zombie_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AZombie_KJY : public AZombieBase_KJY
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
