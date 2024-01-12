// zombie must die


#include "PlayerAnimInstance.h"

#include "Character/Player/PlayerBase_YMH.h"

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

		// 회전값 적용
		pitchAngle = -Player->GetBaseAimRotation().GetNormalized().Pitch;
		pitchAngle = FMath::Clamp(pitchAngle, -60, 60);

		bIsCombat = Player->bIsCombat;
	}
}

void UPlayerAnimInstance::PlayFireAnimation()
{
	if (fireMontage)
	{
		Montage_Play(fireMontage);
	}
}

void UPlayerAnimInstance::PlayReloadAnimation()
{
	if (reloadMontage)
	{
		Montage_Play(reloadMontage);
	}
}

void UPlayerAnimInstance::AnimNotify_Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("OnReload"));
	Player->bulletCount = SMGBulletCount;
	Player->bIsReloading = false;
}
