// zombie must die


#include "PlayerFireComp_YMH.h"

#include "EnhancedInputComponent.h"
#include "FrameTypes.h"
#include "Animation/AnimInstance.h"
#include "PlayerBase_YMH.h"
#include "Actor/Bullet_YMH.h"
#include "Animation/PlayerAnimInstance_YMH.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/ZombieAnim.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"

UPlayerFireComp_YMH::UPlayerFireComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_FireRef(TEXT("/Script/EnhancedInput.InputAction'/Game/YMH/Inputs/Actions/IA_Fire_YMH.IA_Fire_YMH'"));
	if (IA_FireRef.Succeeded())
	{
		IA_Fire = IA_FireRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ReloadRef(TEXT("/Script/EnhancedInput.InputAction'/Game/YMH/Inputs/Actions/IA_Reload_YMH.IA_Reload_YMH'"));
	if (IA_ReloadRef.Succeeded())
	{
		IA_Reload = IA_ReloadRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ZoomRef(TEXT("/Script/EnhancedInput.InputAction'/Game/YMH/Inputs/Actions/IA_Zoom_YMH.IA_Zoom_YMH'"));
	if (IA_ZoomRef.Succeeded())
	{
		IA_Zoom = IA_ZoomRef.Object;
	}
}

void UPlayerFireComp_YMH::BeginPlay()
{
	Super::BeginPlay();
	auto player1 = Cast<APlayerBase_YMH>(GetOwner()); 
	localPlayer = Cast<APlayerController_YMH>(player1->GetController());
}

void UPlayerFireComp_YMH::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (localPlayer && localPlayer->IsLocalController())
	{
		bulletDropPoint = (player->Weapon->GetSocketLocation(FName("Muzzle"))) + (player->FollowCamera->GetForwardVector() * attackDistance);
	}
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

		// Zoom
		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Started, this, &UPlayerFireComp_YMH::ZoomIn);
		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Completed, this, &UPlayerFireComp_YMH::ZoomOut);
	}
}

void UPlayerFireComp_YMH::weaponeUpgrade()
{
	Damage++;
}

void UPlayerFireComp_YMH::Fire(const FInputActionValue& value)
{
	if (bulletCount <= 0 || player->bIsReloading || player->bIsBuildMode || player->fireDispatcher || player->bIsDead)
	{
		return;
	}

	ServerRPCFire();
}

void UPlayerFireComp_YMH::ZoomIn(const FInputActionValue& value)
{
	player->FollowCamera->FieldOfView = maxFOV;
	player->bIsCombat = true;
	bZoomIn = true;
}

void UPlayerFireComp_YMH::ZoomOut(const FInputActionValue& value)
{
	player->FollowCamera->FieldOfView = defaultFOV;
	player->bIsCombat = false;
	bZoomIn = false;
}

void UPlayerFireComp_YMH::Reload(const FInputActionValue& value)
{
	// UE_LOG(LogTemp, Warning, TEXT("Reload"));

	if (player->bIsReloading || player->bIsBuildMode || player->fireDispatcher || player->bIsDead)
	{
		return;
	}
	
	ServerRPCReload();
}

void UPlayerFireComp_YMH::ServerRPCReload_Implementation()
{
	ClientRPCReload_Implementation();
	MultiRPCReload();
}

void UPlayerFireComp_YMH::ClientRPCReload_Implementation()
{
	player->bIsReloading = true;
}

void UPlayerFireComp_YMH::MultiRPCReload_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), player->reloadSound);
	auto anim = Cast<UPlayerAnimInstance_YMH>(player->GetMesh()->GetAnimInstance());
	anim->PlayReloadAnimation();
}

void UPlayerFireComp_YMH::ServerRPCInitAmmo_Implementation()
{
	bulletCount += reloadBulletCount;

	if (bulletCount > MaxBulletCount)
	{
		bulletCount = MaxBulletCount;
	}
	
	ClientRPCInitAmmo(bulletCount);
}

void UPlayerFireComp_YMH::ClientRPCInitAmmo_Implementation(const int bc)
{
	if (PlayerController)
	{
		PlayerController->mainUI->CurrentBullet->SetText(FText::AsNumber(bc));
	}
	player->bIsReloading = false;
}

void UPlayerFireComp_YMH::ServerRPCFire_Implementation()
{
	FVector startPos = player->FollowCamera->GetComponentLocation();
	FVector endPos = startPos + player->FollowCamera->GetForwardVector() * attackDistance;
	
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);
	
	FHitResult hitInfo;
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
	FHitResult hitInfoZombie;
	bool bHitZombie = GetWorld()->LineTraceSingleByChannel(hitInfoZombie, startPos, endPos, ECC_GameTraceChannel3, params);
	
	
	if (bHitZombie)
	{
		//enemy 체력--
		auto Enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
		auto Temp = Cast<UZombieFSM>(Enemy);
		if (Temp)
		{
			auto MyEnemy = Cast<AZombieBase_KJY>(Temp->GetOwner());
			MyEnemy->ServerRPCDamage(Damage);
		}
	}

	if (bHit)
	{
		// hitInfo.location을 Bullet도착 지점으로
		bulletDropPoint = hitInfo.Location;
	}

	bulletCount--;

	FTransform firePosition = player->Weapon->GetSocketTransform(TEXT("Muzzle"));

	MultiRPCFire(bHit, bHitZombie, hitInfo, hitInfoZombie, bulletCount, firePosition);
	ClientRPCFire(bulletCount);

	if (BulletFactory)
	{
		GetWorld()->SpawnActor<ABullet_YMH>(BulletFactory, firePosition);
	}
}

void UPlayerFireComp_YMH::MultiRPCFire_Implementation(bool bHit, bool bHitZombie, const FHitResult& hitInfo, const FHitResult& hitInfoZombie, const int bc, FTransform firePosition)
{
	player->fireDispatcher = true;
	GetWorld()->GetTimerManager().ClearTimer(combatHandle);

	if (bHit && bulletDecal)
	{
		FRotator newRot = UKismetMathLibrary::MakeRotFromX(hitInfo.ImpactNormal);
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), bulletDecal, decalSize, hitInfo.Location, newRot, 10.0f);
		// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), defaultBulletMark, hitInfo.Location, FRotator());
	}

	if (bHitZombie && bulletMark)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletMark, hitInfoZombie.Location, FRotator());
	}
	
	auto anim = Cast<UPlayerAnimInstance_YMH>(player->GetMesh()->GetAnimInstance());
	anim->PlayFireAnimation();
	
	player->bIsCombat = true;
	GetWorld()->GetTimerManager().SetTimer(combatHandle, FTimerDelegate::CreateLambda([&]
	{
		if (bZoomIn == false)
		{
			player->bIsCombat = false;
		}
	}), 5, true);

	if (muzzleFire)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), muzzleFire, player->Weapon->GetSocketLocation(FName("Muzzle")), FRotator());
	}
	UGameplayStatics::PlaySound2D(GetWorld(), player->fireSound);
}

void UPlayerFireComp_YMH::ClientRPCFire_Implementation(const int bc)
{
	if (PlayerController)
	{
		PlayerController->mainUI->weaponRecoil();
		PlayerController->mainUI->CurrentBullet->SetText(FText::AsNumber(bc));
	}

	float pitchInput = FMath::RandRange(MinRecoilValue, MaxRecoilValue);
	player->AddControllerPitchInput(pitchInput);
}