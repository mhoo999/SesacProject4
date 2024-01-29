// zombie must die


#include "Zombie_KJY.h"

#include "ZombieAnim.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"


void AZombie_KJY::BeginPlay()
{
	Super::BeginPlay();
}

void AZombie_KJY::SpawnItem()
{
	Super::SpawnItem();
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Purple, TEXT("22222222222222222222222"));

}