// zombie must die


#include "PlayerBase_YMH.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NetworkMessage.h"
#include "PlayerBuildComp_LDJ.h"
#include "PlayerFireComp_YMH.h"
#include "PlayerInteractComp_LDJ.h"
#include "PlayerMoveComp_YMH.h"
#include "PlayerUpgradeComp_YMH.h"
#include "SMGPlayer_YMH.h"
#include "WaveStartComp_LDJ.h"
#include "Animation/PlayerAnimInstance_YMH.h"
#include "Components/Border.h"
#include "Components/CapsuleComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/TextBlock.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/MoneyWidget_LDJ.h"

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
	SelfCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	// SceneCapture > HiddenShoFlags > Lighting = false 하면 캐릭터 밝게 나옴 
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	
	GetMesh()->SetRelativeRotation(FRotator(0, -65, 0));

	MoveComp = CreateDefaultSubobject<UPlayerMoveComp_YMH>(TEXT("Movement Component"));
	FireComp = CreateDefaultSubobject<UPlayerFireComp_YMH>(TEXT("Fire Component"));
	BuildComp = CreateDefaultSubobject<UPlayerBuildComp_LDJ>(TEXT("Build Component"));
	UpgradeComp = CreateDefaultSubobject<UPlayerUpgradeComp_YMH>(TEXT("Upgrade Component"));
	WaveStartComp = CreateDefaultSubobject<UWaveStartComp_LDJ>(TEXT("Wave Start Component"));
	InteractComp = CreateDefaultSubobject<UPlayerInteractComp_LDJ>(TEXT("Interact Component"));
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

	playerController = Cast<APlayerController_YMH>(GetController());
	
	SetCrosshair();
	
	RenderTarget = NewObject<UTextureRenderTarget2D>();
	RenderTarget->InitCustomFormat(256, 256, EPixelFormat::PF_FloatRGBA, false);
	SelfCapture->TextureTarget = RenderTarget;
	
	// RenderCapture 에서 캡처하고 싶은 Component
	SelfCapture->ShowOnlyComponent(GetMesh());
	SelfCapture->ShowOnlyComponent(Weapon);
	
	TObjectPtr<UMaterialInstanceDynamic> FrameMaterial = UMaterialInstanceDynamic::Create(FrameMaterialInterface, this);
	FrameMaterial->SetTextureParameterValue("RenderTarget", RenderTarget);
	
	if (playerController)
	{
		playerController->mainUI->CharacterFrame->SetBrushFromMaterial(FrameMaterial);
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

void APlayerBase_YMH::VictoryProcess()
{
	auto anim = Cast<UPlayerAnimInstance_YMH>(GetMesh()->GetAnimInstance());
	anim->PlayVictoryMontage();

	DefaultMappingContext = nullptr;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
}

void APlayerBase_YMH::SetCrosshair()
{
	// virtual function
}

void APlayerBase_YMH::BeShot(float damage)
{
	currentHealth -= damage;
	UE_LOG(LogTemp, Warning, TEXT("Damege!"));

	if (currentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead!"));
		bIsDead = true;
		ServerRPCIsdead_Implementation(bIsDead);

		DefaultMappingContext = nullptr;
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->DisableMovement();
	}
	
	float percent = currentHealth / maxHelth;
	
	if (playerController)
	{
		playerController->mainUI->hp = percent;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), hitSound);
}

void APlayerBase_YMH::ServerRPCIsdead_Implementation(bool isDead)
{
	MultiRPCIsdead_Implementation(isDead);
}

void APlayerBase_YMH::MultiRPCIsdead_Implementation(bool isDead)
{
	bIsDead = true;
}

void APlayerBase_YMH::DieProcess()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, TEXT("YOU DIE"));
	
	FollowCamera->PostProcessSettings.ColorSaturation = FVector4(0, 0, 0, 1);

	auto pc = Cast<APlayerController>(Controller);
	// pc->SetShowMouseCursor(true);
	
	if(playerController)
	{
		playerController->mainUI->img_pointer->SetVisibility(ESlateVisibility::Hidden);
		playerController->mainUI->img_cresshair->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerBase_YMH::RestorationHealth(float value)
{
	currentHealth += value;
}
