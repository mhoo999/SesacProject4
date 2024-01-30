// zombie must die


#include "Actor/HealthItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Kismet/GameplayStatics.h"

void AHealthItem_KJY::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HealthPosionDropSound, GetActorLocation());
}

void AHealthItem_KJY::ReactItem()
{
	if (Player->IsLocallyControlled())
	{
		Player->currentHealth+=3;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HealthPosionEatSound, GetActorLocation());
}
