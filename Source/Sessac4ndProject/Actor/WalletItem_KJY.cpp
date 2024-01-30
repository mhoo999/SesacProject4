// zombie must die


#include "Actor/WalletItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"

void AWalletItem_KJY::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());
}

void AWalletItem_KJY::ReactItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());

	Player->wallet+=50;
}
