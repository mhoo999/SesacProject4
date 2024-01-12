// zombie must die


#include "PlayerBase_YMH.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerFireComp.h"
#include "PlayerMoveComp_YMH.h"

APlayerBase_YMH::APlayerBase_YMH()
{
	// 컨트롤러의 방향으로 캐릭터를 회전(false)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// 가속되는 방향으로 캐릭터 메쉬를 회전(false)
	GetCharacterMovement()->bOrientRotationToMovement = false;
	// 컨트롤러의 방향으로 캐릭터를 부드럽게 회전(true)
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 280.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 70, 80));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	// Pawn 기준으로 Rotation 값을 가져올 것인가?
	FollowCamera->bUsePawnControlRotation = false;

	MoveComp = CreateDefaultSubobject<UPlayerMoveComp_YMH>(TEXT("Movement Component"));
	FireComp = CreateDefaultSubobject<UPlayerFireComp>(TEXT("Fire Component"));
}

void APlayerBase_YMH::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerBase_YMH::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerBase_YMH::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	OnSetupInputDelegate.Broadcast(PlayerInputComponent);
}

void APlayerBase_YMH::InstallTrap()
{
}

void APlayerBase_YMH::Selector()
{
}
