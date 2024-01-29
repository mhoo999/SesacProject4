// zombie must die


#include "Actor/SkillUpItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"

void AItemActor_KJY::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player->skillPoint+1;
	Destroy();
}
