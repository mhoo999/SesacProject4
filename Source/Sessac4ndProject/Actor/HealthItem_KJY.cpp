// zombie must die


#include "Actor/HealthItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"

void AHealthItem_KJY::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());
}

void AHealthItem_KJY::ReactItem()
{
	Player->currentHealth+=3;
}
