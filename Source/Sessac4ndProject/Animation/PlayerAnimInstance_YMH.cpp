// zombie must die


#include "PlayerAnimInstance_YMH.h"

#include "Character/Player/PlayerBase_YMH.h"

void UPlayerAnimInstance_YMH::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<APlayerBase_YMH>(TryGetPawnOwner());
}

void UPlayerAnimInstance_YMH::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player)
	{
		FVector velocity = Player->GetVelocity();
		speed = FVector::DotProduct(velocity, Player->GetActorForwardVector());
		direction = FVector::DotProduct(velocity, Player->GetActorRightVector());

		// 회전값 적용
		pitchAngle = -Player->GetBaseAimRotation().GetNormalized().Pitch;
		pitchAngle = FMath::Clamp(pitchAngle, -60, 60);

		bIsCombat = Player->bIsCombat;
	}
}

void UPlayerAnimInstance_YMH::PlayFireAnimation()
{
	if (fireMontage)
	{
		Montage_Play(fireMontage);
	}
}

void UPlayerAnimInstance_YMH::PlayReloadAnimation()
{
	if (reloadMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reload Start!"));
		Montage_Play(reloadMontage);
	}
}

void UPlayerAnimInstance_YMH::AnimNotify_Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("OnReload"));
	Player->bulletCount = SMGBulletCount;
	Player->bIsReloading = false;
}
