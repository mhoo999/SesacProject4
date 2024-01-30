// zombie must die


#include "Character/Player/PlayerBuildComp_LDJ.h"

#include <functional>

#include "EnhancedInputComponent.h"
#include "PlayerBase_YMH.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Trap/FlameThrowerTrap_LDJ.h"
#include "Trap/FreezeTrap_LDJ.h"
#include "Trap/PoisonTrap_LDJ.h"
#include "Trap/SpikeTrap_LDJ.h"
#include "InputAction.h"
#include "PlayerUpgradeComp_YMH.h"
#include "Animation/PlayerAnimInstance_YMH.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieManagerBase_KJY.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/MoneyWidget_LDJ.h"
#include "UI/TrapAndWeaponLevelUI_LDJ.h"
#include "UI/WaveInformationUI_LDJ.h"


UPlayerBuildComp_LDJ::UPlayerBuildComp_LDJ()
{
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UStaticMeshComponent> StaticMeshCompRef(TEXT("/Script/Engine.StaticMeshComponent"));
	if (StaticMeshCompRef.Succeeded())
	{
		PreviewMeshFactory = StaticMeshCompRef.Class;
		PreviewTrap = PreviewMeshFactory.GetDefaultObject();
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PreviewTrapMeshRef(TEXT("/Game/SimpleApocalypse/Meshes/Environment/SM_Env_ManholeClosed_01.SM_Env_ManholeClosed_01"));
	if (PreviewTrapMeshRef.Succeeded()) PreviewTrapMesh = PreviewTrapMeshRef.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> EnableMeshRef(TEXT("/Game/LDJ/Blueprints/M_BuildingPreview.M_BuildingPreview"));
	if (EnableMeshRef.Succeeded()) EnableMesh = EnableMeshRef.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DisableMeshRef(TEXT("/Script/Engine.Material'/Game/LDJ/Blueprints/M_DisablePreview.M_DisablePreview'"));
	if (DisableMeshRef.Succeeded()) DisableMesh = DisableMeshRef.Object;

	static ConstructorHelpers::FClassFinder<ASpikeTrap_LDJ> SpikeTrapRef(TEXT("/Game/LDJ/Blueprints/BP_SpikeTrap_LDJ.BP_SpikeTrap_LDJ_C"));
	if (SpikeTrapRef.Succeeded()) SpikeTrapFactory = SpikeTrapRef.Class;

	static ConstructorHelpers::FClassFinder<AFreezeTrap_LDJ> FreezeTrapRef(TEXT("/Game/LDJ/Blueprints/BP_FreezeTrap_LDJ.BP_FreezeTrap_LDJ_C"));
	if (FreezeTrapRef.Succeeded()) FreezeTrapFactory = FreezeTrapRef.Class;

	static ConstructorHelpers::FClassFinder<APoisonTrap_LDJ> PoisonTrapRef(TEXT("/Game/LDJ/Blueprints/BP_PoisonTrap_LDJ.BP_PoisonTrap_LDJ_C"));
	if (PoisonTrapRef.Succeeded()) PoisonTrapFactory = PoisonTrapRef.Class;

	static ConstructorHelpers::FClassFinder<AFlameThrowerTrap_LDJ> FlameTrapRef(TEXT("/Game/LDJ/Blueprints/BP_FlameThrowerTrap_LDJ.BP_FlameThrowerTrap_LDJ_C"));
	if (FlameTrapRef.Succeeded()) FlameTrapFactory = FlameTrapRef.Class;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ChooseTrap1Ref(TEXT("/Game/YMH/Inputs/Actions/IA_ChooseTrap1_YMH.IA_ChooseTrap1_YMH"));
	if (IA_ChooseTrap1Ref.Succeeded()) IA_ChooseTrap1 = IA_ChooseTrap1Ref.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ChooseTrap2Ref(TEXT("/Game/YMH/Inputs/Actions/IA_ChooseTrap2_YMH.IA_ChooseTrap2_YMH"));
	if (IA_ChooseTrap2Ref.Succeeded()) IA_ChooseTrap2 = IA_ChooseTrap2Ref.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ChooseTrap3Ref(TEXT("/Game/YMH/Inputs/Actions/IA_ChooseTrap3_YMH.IA_ChooseTrap3_YMH"));
	if (IA_ChooseTrap3Ref.Succeeded()) IA_ChooseTrap3 = IA_ChooseTrap3Ref.Object;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ChooseTrap4Ref(TEXT("/Game/YMH/Inputs/Actions/IA_ChooseTrap4_YMH.IA_ChooseTrap4_YMH"));
	if (IA_ChooseTrap4Ref.Succeeded()) IA_ChooseTrap4 = IA_ChooseTrap4Ref.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ChooseWeaponRef(TEXT("/Game/YMH/Inputs/Actions/IA_ChooseWeapon_YMH.IA_ChooseWeapon_YMH"));
	if (IA_ChooseWeaponRef.Succeeded()) IA_ChooseWeapon = IA_ChooseWeaponRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_PlaceTrapRef(TEXT("/Game/YMH/Inputs/Actions/IA_Fire_YMH.IA_Fire_YMH"));
	if (IA_PlaceTrapRef.Succeeded()) IA_PlaceTrap = IA_PlaceTrapRef.Object;

	// static ConstructorHelpers::FObjectFinder<UInputAction> IA_WaveStartRef(TEXT("/Game/LDJ/Input/IA_WaveStart.IA_WaveStart"));
	// if (IA_WaveStartRef.Succeeded()) IA_WaveStart = IA_WaveStartRef.Object;
	
	// static ConstructorHelpers::FClassFinder<UWaveInformationUI_LDJ> WaveInforUIRef(TEXT("/Game/LDJ/UI/WBP_WaveInfor.WBP_WaveInfor_C"));
	// if (WaveInforUIRef.Succeeded()) WaveInforUIFactory = WaveInforUIRef.Class;

	static ConstructorHelpers::FObjectFinder<USoundBase> BuildSoundRef(TEXT("/Game/Resources/LDJ/Sounds/Trap/TrapBuiltSound2.TrapBuiltSound2"));
	if (BuildSoundRef.Succeeded())
	{
		BuiltSound = BuildSoundRef.Object;
	}
}

void UPlayerBuildComp_LDJ::BeginPlay()
{
	Super::BeginPlay();
	// LevelUpUI = Cast<UTrapAndWeaponLevelUI_LDJ>(CreateWidget(GetWorld(), LevelUpUIFactory));
	// LevelUpUI->AddToViewport();
	// WaveInforUI = Cast<UWaveInformationUI_LDJ>(CreateWidget(GetWorld(), WaveInforUIFactory));
	// WaveInforUI->AddToViewport();
	UpgradeComp = player->FindComponentByClass<UPlayerUpgradeComp_YMH>();
}

void UPlayerBuildComp_LDJ::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (player->bIsBuildMode)
	{
		PreviewLoop();
	}
}

void UPlayerBuildComp_LDJ::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Build
		EnhancedInputComponent->BindAction(IA_ChooseTrap1, ETriggerEvent::Started, this,
		                                   &UPlayerBuildComp_LDJ::DoBuildSpikeTrap);
		EnhancedInputComponent->BindAction(IA_ChooseTrap2, ETriggerEvent::Started, this,
		                                   &UPlayerBuildComp_LDJ::DoBuildFreezeTrap);
		EnhancedInputComponent->BindAction(IA_ChooseTrap3, ETriggerEvent::Started, this,
		                                   &UPlayerBuildComp_LDJ::DoBuildPoisonTrap);
		EnhancedInputComponent->BindAction(IA_ChooseTrap4, ETriggerEvent::Started, this,
		                                   &UPlayerBuildComp_LDJ::DoBuildFlameTrap);
		EnhancedInputComponent->BindAction(IA_ChooseWeapon, ETriggerEvent::Started, this,
		                                   &UPlayerBuildComp_LDJ::DoEquipGun);
		EnhancedInputComponent->BindAction(IA_PlaceTrap, ETriggerEvent::Started, this,
		                                   &UPlayerBuildComp_LDJ::PressPlaceBuild);
		// Trap Upgrade Input
		// EnhancedInputComponent->BindAction(IA_LevelUpBtn, ETriggerEvent::Started, this,
		// 				   &UPlayerBuildComp_LDJ::LevelUp);
		// EnhancedInputComponent->BindAction(IA_WaveStart, ETriggerEvent::Started, this,
		// 		   &UPlayerBuildComp_LDJ::WaveStart);
	}
}

void UPlayerBuildComp_LDJ::DoBuildSpikeTrap(const FInputActionValue& value)
{
	player->bIsBuildMode = true;
	TrapFactory = SpikeTrapFactory;
	SelectedTrap = NewObject<ASpikeTrap_LDJ>(TrapFactory);
	SelectedTrap->Cost += UpgradeComp->SpikeTrapLevel * 25;
	
	if (PlayerController)
	{
		PlayerController->mainUI->SelectSlot(1);
		PlayerController->mainUI->img_cresshair->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->mainUI->img_pointer->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerBuildComp_LDJ::DoBuildFreezeTrap(const FInputActionValue& value)
{
	player->bIsBuildMode = true;
	TrapFactory = FreezeTrapFactory;
	SelectedTrap = NewObject<AFreezeTrap_LDJ>(TrapFactory);
	SelectedTrap->Cost += UpgradeComp->FreezeTrapLevel * 25;
	
	if (PlayerController)
	{
		PlayerController->mainUI->SelectSlot(2);
		PlayerController->mainUI->img_cresshair->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->mainUI->img_pointer->SetVisibility(ESlateVisibility::Hidden);

	}
}

void UPlayerBuildComp_LDJ::DoBuildPoisonTrap(const FInputActionValue& value)
{
	player->bIsBuildMode = true;
	TrapFactory = PoisonTrapFactory;
	SelectedTrap = NewObject<APoisonTrap_LDJ>(TrapFactory);
	SelectedTrap->Cost += UpgradeComp->PoisonTrapLevel * 25;
	
	if (PlayerController)
	{
		PlayerController->mainUI->SelectSlot(3);
		PlayerController->mainUI->img_cresshair->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->mainUI->img_pointer->SetVisibility(ESlateVisibility::Hidden);

	}
}

void UPlayerBuildComp_LDJ::DoBuildFlameTrap(const FInputActionValue& value)
{
	player->bIsBuildMode = true;
	TrapFactory = FlameTrapFactory;
	SelectedTrap = NewObject<AFlameThrowerTrap_LDJ>(TrapFactory);
	SelectedTrap->Cost += UpgradeComp->FlameTrapLevel * 25;
	
	if (PlayerController)
	{
		PlayerController->mainUI->SelectSlot(4);
		PlayerController->mainUI->img_cresshair->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->mainUI->img_pointer->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerBuildComp_LDJ::DoEquipGun(const FInputActionValue& value)
{
	player->bIsBuildMode = false;
	
	if (PreviewTrap)
	{
		PreviewTrap->SetStaticMesh(nullptr);
		TrapFactory = nullptr;
		// SelectedTrap = nullptr;
	}
	bDoOnceMeshSet = false;

	if (PlayerController)
	{
		PlayerController->mainUI->SelectSlot(0);
		player->SetCrosshair();
	}
}

void UPlayerBuildComp_LDJ::PreviewLoop()
{
	FVector StartPos = player->FollowCamera->GetComponentLocation();
	FVector EndPos = StartPos + player->FollowCamera->GetForwardVector() * 2000;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(player);
	FHitResult HitInfo;
	auto temp = GetWorld()->LineTraceSingleByChannel(HitInfo, StartPos, EndPos, ECC_Visibility, Params);
	if (temp)
	{
		if (!bDoOnceMeshSet) this->ResetPreviewMesh();
	}
	
	TempVec = FVector(HitInfo.Location.X, HitInfo.Location.Y, HitInfo.Location.Z);
	TempVec.X = FMath::Floor(HitInfo.Location.X / 350) * 350 + 190;
	TempVec.Y = FMath::Floor(HitInfo.Location.Y / 350) * 350 + 250;
	// TempVec.Z = FMath::CeilToFloat(HitInfo.Location.Z);
	TempVec.Z = 0;
	BuildPreviewTransform.SetLocation(TempVec);
	BuildPreviewTransform.SetScale3D(FVector(2.15, 2.15, 1));

	if (PreviewTrap)
	{
		PreviewTrap->SetWorldTransform(BuildPreviewTransform);
	}
}

void UPlayerBuildComp_LDJ::ResetPreviewMesh()
{
	auto temp = player->AddComponentByClass(PreviewMeshFactory, false, BuildPreviewTransform, false);
	PreviewTrap = Cast<UStaticMeshComponent>(temp);
	if (temp && !bDoOnceMeshSet)
	{
		PreviewTrap->SetStaticMesh(PreviewTrapMesh);
		if (player->wallet >= SelectedTrap->GetCost())
		{
			PreviewTrap->SetMaterial(0, EnableMesh);
		}
		else
		{
			PreviewTrap->SetMaterial(0, DisableMesh);
		}
		PreviewTrap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PreviewTrap->SetCollisionProfileName(FName("Trap"));
		// PreviewTrap->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PreviewTrap->SetGenerateOverlapEvents(true);

		PreviewTrap->OnComponentBeginOverlap.AddDynamic(this, &UPlayerBuildComp_LDJ::OnTrapBeginOverlapped);
		PreviewTrap->OnComponentEndOverlap.AddDynamic(this, &UPlayerBuildComp_LDJ::OnTrapEndOverlapped);
		bDoOnceMeshSet = true;
	}
}

void UPlayerBuildComp_LDJ::PressPlaceBuild()
{
	if (player->bIsBuildMode && bBuildEnable && player->wallet >= SelectedTrap->GetCost())
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, FString::Printf(TEXT("%p"), GetWorld()->GetFirstPlayerController()));
		auto anim = Cast<UPlayerAnimInstance_YMH>(player->GetMesh()->GetAnimInstance());
		anim->PlayInstallMontage();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BuiltSound, GetOwner()->GetActorLocation());
		
		// GetWorld()->SpawnActor<ATrapBase>(TrapFactory, BuildPreviewTransform);
		ServerRPC_PressPlaceBuild(TempVec, TrapFactory);
	}
}

void UPlayerBuildComp_LDJ::OnTrapEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
											   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Temp = Cast<ATrapBase>(OtherActor);
	if (Temp)
	{
		CollisionMeshCnt--;
		if (CollisionMeshCnt == 0)
		{
			PreviewTrap->SetMaterial(0, EnableMesh);
			bBuildEnable = true;
		}
	}

	if (player->wallet < SelectedTrap->Cost)
	{
		PreviewTrap->SetMaterial(0, DisableMesh);
	}
}

void UPlayerBuildComp_LDJ::OnTrapBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
	auto Temp = Cast<ATrapBase>(OtherActor);
	if (Temp)
	{
		CollisionMeshCnt++;
		if (CollisionMeshCnt)
		{
			PreviewTrap->SetMaterial(0, DisableMesh);
			bBuildEnable = false;
		}
	}
}

// 네트워크

void UPlayerBuildComp_LDJ::ServerRPC_PressPlaceBuild_Implementation(const FVector& Vec, TSubclassOf<ATrapBase> RPCTrapFactory)
{
	BuildPreviewTransform.SetLocation(Vec);
	BuildPreviewTransform.SetScale3D(FVector(0.98));
	GetWorld()->SpawnActor<ATrapBase>(RPCTrapFactory, BuildPreviewTransform);
	ClientRPC_PressPlaceBuild(Vec);
}

void UPlayerBuildComp_LDJ::ClientRPC_PressPlaceBuild_Implementation(const FVector& Vec)
{
	auto Player = Cast<APlayerBase_YMH>(PlayerController->GetPawn());
	if (Player)
	{
		Player->wallet = Player->wallet - SelectedTrap->GetCost();
		PlayerController->mainUI->WBP_Money->SetMoneyText(Player->wallet);
	}
}