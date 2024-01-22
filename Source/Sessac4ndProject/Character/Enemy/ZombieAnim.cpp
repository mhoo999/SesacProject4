// zombie must die


#include "ZombieAnim.h"


void UZombieAnim::PlayDamageAnim()
{
	Montage_Play(DamageAnimMontage);
}


void UZombieAnim::PlayDieAnim()
{
	Montage_Play(DieAnimMontage);
}

void UZombieAnim::OnEndAttackAnimation()
{
	bAttackPlay = false;
}
