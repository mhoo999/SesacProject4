// zombie must die


#include "ZombieAnim.h"

#include "ZombieBase_KJY.h"


void UZombieAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Me)
	{
		bIsDead = Me->bZombieDie;
		bIsDamage = Me->bZombieHit;
	}
}

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

void UZombieAnim::AnimNotify_Attack()
{
	bAttackCollision = true;
	UE_LOG(LogTemp, Warning, TEXT("notify"));
}

void UZombieAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Me = Cast<AZombieBase_KJY>(GetOwningActor());
	
}

void UZombieAnim::AnimNotify_ReactEnd()
{
	Me->bZombieHit = false;
}
