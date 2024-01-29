// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "FastZombie_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AFastZombie_KJY : public AZombieBase_KJY
{
	GENERATED_BODY()

public:
	AFastZombie_KJY();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
