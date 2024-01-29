// zombie must die


#include "Trap/PoisonTrap_LDJ.h"

#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"
#include "Character/Enemy/Zombie_KJY.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Character/Player/PlayerUpgradeComp_YMH.h"


APoisonTrap_LDJ::APoisonTrap_LDJ()
{
	PoisonBottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Poison Bottle Mesh"));
	PoisonBottleMesh->SetupAttachment(TileMesh);
	PoisonBottleMesh->SetRelativeLocation(FVector(-50,-45,27));
	PoisonBottleMesh->SetRelativeRotation(FRotator(-90.f,0,40));
	PoisonBottleMesh->SetRelativeScale3D(FVector(0.5));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BottleMeshRef(TEXT("/Game/SimpleApocalypse/Meshes/Items/SM_Item_Whisky_01.SM_Item_Whisky_01"));
	if (BottleMeshRef.Succeeded())
	{
		PoisonBottleMesh->SetStaticMesh(BottleMeshRef.Object);
	}

	PoisonLiquid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Poison Liquid Mesh"));
	PoisonLiquid->SetupAttachment(TileMesh);
	PoisonLiquid->SetRelativeLocation(FVector(0,0,18));
	PoisonLiquid->SetRelativeScale3D(FVector(0.8f,0.8f, 1.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PoisonLiquidRef(TEXT("/Game/SimpleApocalypse/Meshes/Props/SM_Prop_Bloodstain_01.SM_Prop_Bloodstain_01"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PoisonLiquidMatRef(TEXT("/Engine/EngineDebugMaterials/VertexColorViewMode_GreenOnly.VertexColorViewMode_GreenOnly"));
	if (PoisonLiquidRef.Succeeded()) PoisonLiquid->SetStaticMesh(PoisonLiquidRef.Object);
	if (PoisonLiquidMatRef.Succeeded()) PoisonLiquid->SetMaterial(0, PoisonLiquidMatRef.Object);
}

void APoisonTrap_LDJ::BeginPlay()
{
	Super::BeginPlay();
	TrapLevel = PlayerUpgradeComp->PoisonTrapLevel;
}

void APoisonTrap_LDJ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 APoisonTrap_LDJ::GetCost()
{
	return this->Cost;
}

void APoisonTrap_LDJ::UpgradeAbility()
{
	
}

void APoisonTrap_LDJ::ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef)
{
	for (auto e : EnemyBoxRef) e->CustomTimeDilation = (0.25f - 0.8 * TrapLevel);
}
