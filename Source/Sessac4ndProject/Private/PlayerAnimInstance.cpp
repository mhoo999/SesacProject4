// zombie must die


#include "PlayerAnimInstance.h"

#include "PlayerBase_YMH.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<APlayerBase_YMH>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player)
	{
		FVector velocity = Player->GetVelocity();
		speed = FVector::DotProduct(velocity, Player->GetActorForwardVector());
		direction = FVector::DotProduct(velocity, Player->GetActorRightVector());
	}
}

void UPlayerAnimInstance::PlayFireAnimation()
{
	if (fireMontage)
	{
		Montage_Play(fireMontage);
	}
}
