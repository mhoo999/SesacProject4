// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZMDGameInstance_LDJ.generated.h"

/**
 * 
 */
UCLASS()
class SESSAC4NDPROJECT_API UZMDGameInstance_LDJ : public UGameInstance
{
	GENERATED_BODY()

public:
	UZMDGameInstance_LDJ();
	virtual void Init() override;
};
