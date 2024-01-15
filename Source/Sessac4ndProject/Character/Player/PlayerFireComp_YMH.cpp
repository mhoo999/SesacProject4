// zombie must die


#include "PlayerFireComp_YMH.h"

#include "EnhancedInputComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerBase_YMH.h"
#include "Animation/PlayerAnimInstance_YMH.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/ZombieAnim.h"
#include "Kismet/GameplayStatics.h"

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

	bIsReloading = player->bIsReloading;
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
	if (player->bulletCount <= 0 || bIsReloading || player->bIsBuildMode)
	{
		return;
	}
	
	currentTime += 0.1f;

	if (currentTime > player->attackSpeed)
	{
		FireBullet();
		currentTime = 0;
	}
}

void UPlayerFireComp_YMH::FireBullet()
{
	GetWorld()->GetTimerManager().ClearTimer(combatHandle);
	
	FHitResult hitInfo;
	FVector startPos = player->FollowCamera->GetComponentLocation();
	FVector endPos = startPos + player->FollowCamera->GetForwardVector() * player->attackDistance;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
	
	if (bHit)
	{
		//enemy 체력--
		auto Enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
		if (Enemy)
		{
			auto EnemyFSM = Cast<UZombieFSM>(Enemy);
			EnemyFSM->Damage();
		}
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletMark, hitInfo.Location, FRotator());
	}

	player->bulletCount--;
	UE_LOG(LogTemp, Warning, TEXT("Bullet Count : %u"), player->bulletCount);

	auto anim = Cast<UPlayerAnimInstance_YMH>(player->GetMesh()->GetAnimInstance());
	anim->PlayFireAnimation();

	player->bIsCombat = true;

	GetWorld()->GetTimerManager().SetTimer(combatHandle, FTimerDelegate::CreateLambda([&]
	{
		player->bIsCombat = false;
	}), 5, true);
}

void UPlayerFireComp_YMH::Reload(const FInputActionValue& value)
{
	// UE_LOG(LogTemp, Warning, TEXT("Reload"));

	if (bIsReloading || player->bIsBuildMode)
	{
		return;
	}
	
	auto anim = Cast<UPlayerAnimInstance_YMH>(player->GetMesh()->GetAnimInstance());
	anim->PlayReloadAnimation();

	bIsReloading = true;
}
