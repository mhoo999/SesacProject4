// zombie must die


#include "PlayerAnimInstance_YMH.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Character/Player/PlayerFireComp_YMH.h"
#include "Components/TextBlock.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"

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
		bIsDead = Player->bIsDead;
		bIsDefeat = Player->bIsDefeat;
	}
}

void UPlayerAnimInstance_YMH::PlayFireAnimation()
{
	if (fireMontage)
	{
		Montage_Play(fireMontage, 2);
	}
}

void UPlayerAnimInstance_YMH::AnimNotify_EndFireDispatcher()
{
	Player->fireDispatcher = false;
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
	Player->FireComp->ServerRPCInitAmmo();
}

void UPlayerAnimInstance_YMH::PlayVictoryMontage()
{
	if (victoryMontage)
	{
		Montage_Play(victoryMontage);
	}
}

void UPlayerAnimInstance_YMH::PlayInstallMontage()
{
	if (installMontage)
	{
		Montage_Play(installMontage, 4, EMontagePlayReturnType::MontageLength, 1.5f);
	}
}

void UPlayerAnimInstance_YMH::AnimNotify_DieEnd()
{
	if (Player && Player->IsLocallyControlled())
	{
		Player->DieProcess();
	}
}
