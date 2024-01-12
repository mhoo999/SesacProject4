// zombie must die


#include "PlayerFireComp.h"

#include "EnhancedInputComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerBase_YMH.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

UPlayerFireComp::UPlayerFireComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerFireComp::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerFireComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerFireComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Fire
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &UPlayerFireComp::Fire);

		// Reload
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Started, this, &UPlayerFireComp::Reload);
	}
}

void UPlayerFireComp::Fire(const FInputActionValue& value)
{
	// UE_LOG(LogTemp, Warning, TEXT("Fire"));

	if (player->bulletCount <= 0)
	{
		// Reload();
		return;
	}
	
	if (fireSpeedHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(fireSpeedHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(fireSpeedHandle, this, &UPlayerFireComp::FireBullet, 0.01, false);
	
	FVector startPos = player->FollowCamera->GetComponentLocation();
	FVector endPos = startPos + player->FollowCamera->GetForwardVector() * 10000;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);
	bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
}

void UPlayerFireComp::FireBullet()
{
	if (bHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletMark, hitInfo.Location, FRotator());
	}

	player->bulletCount--;
	UE_LOG(LogTemp, Warning, TEXT("Bullet Count : %u"), player->bulletCount);

	auto anim = Cast<UPlayerAnimInstance>(player->GetMesh()->GetAnimInstance());
	anim->PlayFireAnimation();
}

void UPlayerFireComp::Reload(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
	player->bulletCount = 30;
}
