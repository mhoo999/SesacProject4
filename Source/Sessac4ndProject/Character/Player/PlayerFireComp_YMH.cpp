// zombie must die


#include "PlayerFireComp_YMH.h"

#include "EnhancedInputComponent.h"
#include "FrameTypes.h"
#include "Animation/AnimInstance.h"
#include "PlayerBase_YMH.h"
#include "Animation/PlayerAnimInstance_YMH.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/ZombieAnim.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"

UPlayerFireComp_YMH::UPlayerFireComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerFireComp_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerFireComp_YMH::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// bIsReloading = player->bIsReloading;
	// fireDispatcher = player->fireDispatcher;
}

void UPlayerFireComp_YMH::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Fire
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &UPlayerFireComp_YMH::Fire);

		// Reload
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Started, this, &UPlayerFireComp_YMH::Reload);
	}
}

void UPlayerFireComp_YMH::Fire(const FInputActionValue& value)
{
	if (bulletCount <= 0 || player->bIsReloading || player->bIsBuildMode || player->fireDispatcher)
	{
		return;
	}

	player->fireDispatcher = true;
	GetWorld()->GetTimerManager().ClearTimer(combatHandle);

	FHitResult hitInfo;
	FVector startPos = player->FollowCamera->GetComponentLocation();
	FVector endPos = startPos + player->FollowCamera->GetForwardVector() * attackDistance;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);

	if (bHit)
	{
		//enemy 체력--
		auto Enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
		auto Temp = Cast<UZombieFSM>(Enemy);
		if (Temp)
		{
			auto MyEnemy = Cast<AZombieBase_KJY>(Temp->GetOwner());
			MyEnemy->Damage();
		}
	
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletMark, hitInfo.Location, FRotator());
	}

	bulletCount--;
	UE_LOG(LogTemp, Warning, TEXT("Bullet Count : %u"), bulletCount);

	auto anim = Cast<UPlayerAnimInstance_YMH>(player->GetMesh()->GetAnimInstance());
	anim->PlayFireAnimation();

	if (PlayerController)
	{
		PlayerController->mainUI->weaponRecoil();
		// MainUI의 CurrentBullet의 값을 빼고 싶다.
		PlayerController->mainUI->CurrentBullet->SetText(FText::AsNumber(bulletCount));
	}
	
	player->bIsCombat = true;

	GetWorld()->GetTimerManager().SetTimer(combatHandle, FTimerDelegate::CreateLambda([&]
	{
		player->bIsCombat = false;
	}), 5, true);
	
	float pitchInput = FMath::RandRange(MinRecoilValue, MaxRecoilValue);
	player->AddControllerPitchInput(pitchInput);
}

void UPlayerFireComp_YMH::Reload(const FInputActionValue& value)
{
	// UE_LOG(LogTemp, Warning, TEXT("Reload"));

	if (player->bIsReloading || player->bIsBuildMode || player->fireDispatcher)
	{
		return;
	}
	
	auto anim = Cast<UPlayerAnimInstance_YMH>(player->GetMesh()->GetAnimInstance());
	anim->PlayReloadAnimation();

	player->bIsReloading = true;
}
