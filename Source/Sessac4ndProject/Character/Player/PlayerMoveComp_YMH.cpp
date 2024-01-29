// zombie must die


#include "PlayerMoveComp_YMH.h"

#include "EnhancedInputComponent.h"
#include "PlayerBase_YMH.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UPlayerMoveComp_YMH::UPlayerMoveComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/YMH/Inputs/Actions/IA_Move_YMH.IA_Move_YMH'"));
	if (IA_MoveRef.Succeeded())
	{
		IA_Move = IA_MoveRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/YMH/Inputs/Actions/IA_Jump_YMH.IA_Jump_YMH'"));
	if (IA_JumpRef.Succeeded())
	{
		IA_Jump = IA_JumpRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/YMH/Inputs/Actions/IA_Look_YMH.IA_Look_YMH'"));
	if (IA_LookRef.Succeeded())
	{
		IA_Look = IA_LookRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_WalkRef(TEXT("/Script/EnhancedInput.InputAction'/Game/YMH/Inputs/Actions/IA_Walk_YMH.IA_Walk_YMH'"));
	if (IA_WalkRef.Succeeded())
	{
		IA_Walk = IA_WalkRef.Object;
	}
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
