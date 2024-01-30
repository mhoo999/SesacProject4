// zombie must die


#include "Actor/SkillUpItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"

void ASkillUpItem_KJY::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());
}

void ASkillUpItem_KJY::ReactItem()
{
	Player->skillPoint+=1;
}
