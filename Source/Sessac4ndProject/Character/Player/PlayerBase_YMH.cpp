// zombie must die


#include "PlayerBase_YMH.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerBuildComp_LDJ.h"
#include "PlayerFireComp_YMH.h"
#include "PlayerMoveComp_YMH.h"
#include "Animation/PlayerAnimInstance_YMH.h"
#include "Components/CapsuleComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"

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

	SelfCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Self CameraBoom"));
	SelfCameraBoom->SetupAttachment(RootComponent);
	SelfCameraBoom->TargetArmLength = 100.0f;
	SelfCameraBoom->SetRelativeRotation(FRotator(0, -145, 0));
	SelfCameraBoom->SetRelativeLocation(FVector(0, 0, 30));

	SelfCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Self Capture"));
	SelfCapture->SetupAttachment(SelfCameraBoom);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight Component"));
	PointLightComp->SetupAttachment(RootComponent);
	PointLightComp->SetRelativeLocation(FVector(55, 15, 20));
	PointLightComp->SetIntensity(1000.0f);
	PointLightComp->SetAttenuationRadius(80.0f);

	GetMesh()->SetRelativeRotation(FRotator(0, -65, 0));

	MoveComp = CreateDefaultSubobject<UPlayerMoveComp_YMH>(TEXT("Movement Component"));
	FireComp = CreateDefaultSubobject<UPlayerFireComp_YMH>(TEXT("Fire Component"));
	BuildComp = CreateDefaultSubobject<UPlayerBuildComp_LDJ>(TEXT("Build Componenet"));
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

	playerController = Cast<APlayerController_YMH>(Controller);
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

void APlayerBase_YMH::BeShot(float damage)
{
	Super::BeShot(damage);

	currentHealth -= damage;
	UE_LOG(LogTemp, Warning, TEXT("Damege!"));

	if (currentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead!"));
		bIsDead = true;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->DisableMovement();
		CameraBoom->bUsePawnControlRotation = false;
		// CameraBoom->SetWorldRotation(FRotator(-45, 0, 0));
	}
	
	float percent = currentHealth / maxHelth;
	
	if (playerController)
	{
		playerController->mainUI->hp = percent;
	}
}

void APlayerBase_YMH::DieProcess()
{
	
	// FollowCamera->PostProcessSettings.ColorSaturation = FVector4(0, 0, 0, 1);

	auto pc = Cast<APlayerController>(Controller);
	pc->SetShowMouseCursor(true);
	
	if(playerController)
	{
		playerController->mainUI->img_pointer->SetVisibility(ESlateVisibility::Hidden);
		playerController->mainUI->img_cresshair->SetVisibility(ESlateVisibility::Hidden);
	}
}
