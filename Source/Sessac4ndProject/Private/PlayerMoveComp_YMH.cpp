// zombie must die


#include "PlayerMoveComp_YMH.h"

#include "EnhancedInputComponent.h"
#include "PlayerBase_YMH.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerMoveComp_YMH::UPlayerMoveComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMoveComp_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMoveComp_YMH::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerMoveComp_YMH::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UPlayerMoveComp_YMH::Move);

		// Jumping
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &UPlayerMoveComp_YMH::Jump);

		// Looking
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &UPlayerMoveComp_YMH::Look);

		// Walking
		EnhancedInputComponent->BindAction(IA_Walk, ETriggerEvent::Started, this, &UPlayerMoveComp_YMH::OnStartWalk);
		EnhancedInputComponent->BindAction(IA_Walk, ETriggerEvent::Completed, this, &UPlayerMoveComp_YMH::OnEndWalk);
	}
}

void UPlayerMoveComp_YMH::Move(const FInputActionValue& value)
{
	// input is a vector 2D
	FVector2d MovementInput = value.Get<FVector2d>();
	
	if (player->Controller != nullptr)
	{
		// find out which way is forward
		const FRotator rotation = player->Controller->GetControlRotation();
		const FRotator YawRotation(0, rotation.Yaw, 0);
		
		// get forward vector
		const FVector forwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector rightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		player->AddMovementInput(forwardDirection, MovementInput.Y);
		player->AddMovementInput(rightDirection, MovementInput.X);
	}
}



void UPlayerMoveComp_YMH::Look(const FInputActionValue& value)
{
	FVector LookAxisVector = value.Get<FVector>();

	if (player->Controller != nullptr)
	{
		player->AddControllerYawInput(LookAxisVector.X);
		player->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void UPlayerMoveComp_YMH::Jump(const FInputActionValue& value)
{
	player->Jump();
}

void UPlayerMoveComp_YMH::OnStartWalk(const FInputActionValue& value)
{
	player->GetCharacterMovement()->MaxWalkSpeed = 200;
}

void UPlayerMoveComp_YMH::OnEndWalk(const FInputActionValue& value)
{
	player->GetCharacterMovement()->MaxWalkSpeed = 600;
}
