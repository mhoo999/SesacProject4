// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Actor/ItemActor_KJY.h"
#include "WalletItem_KJY.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API AWalletItem_KJY : public AItemActor_KJY
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void ReactItem() override;
	
};
