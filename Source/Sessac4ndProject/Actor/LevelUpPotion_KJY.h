// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelUpPotion_KJY.generated.h"

UCLASS()
class SESSAC4NDPROJECT_API ALevelUpPotion_KJY : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelUpPotion_KJY();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
