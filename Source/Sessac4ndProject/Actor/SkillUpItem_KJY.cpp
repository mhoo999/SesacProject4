// zombie must die


#include "Actor/SkillUpItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"

void ASkillUpItem_KJY::ReactItem()
{
	UE_LOG(LogTemp, Warning, TEXT("SkillUp"));

	Player->skillPoint+=1;
}
