// zombie must die


#include "Trap/FlameThrowerTrap_LDJ.h"

#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"
#include "Character/Enemy/Zombie_KJY.h"
#include "Particles/ParticleSystemComponent.h"

AFlameThrowerTrap_LDJ::AFlameThrowerTrap_LDJ()
{
	// FireFX1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh1"));
	// FireFX1->SetupAttachment(TileMesh);
	// FireFX1->SetRelativeLocation((FVector(30, -30, 0)));
	// FireFX1->SetRelativeRotation(FRotator(90, 0, 0));
	// FireFX1->SetVisibility(false);
	//
	// FireFX2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh2"));
	// FireFX2->SetupAttachment(TileMesh);
	// FireFX2->SetRelativeLocation((FVector(30, 30, 0)));
	// FireFX2->SetRelativeRotation(FRotator(90, 0, 0));
	// FireFX2->SetVisibility(false);
	//
	// FireFX3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh3"));
	// FireFX3->SetupAttachment(TileMesh);
	// FireFX3->SetRelativeLocation((FVector(-30, -30, 0)));
	// FireFX3->SetRelativeRotation(FRotator(90, 0, 0));
	// FireFX3->SetVisibility(false);
	//
	//
	// FireFX4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh4"));
	// FireFX4->SetupAttachment(TileMesh);
	// FireFX4->SetRelativeLocation((FVector(-30, 30, 0)));
	// FireFX4->SetRelativeRotation(FRotator(90, 0, 0));
	// FireFX4->SetVisibility(false);
}

void AFlameThrowerTrap_LDJ::BeginPlay()
{
	Super::BeginPlay();
}

void AFlameThrowerTrap_LDJ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlameThrowerTrap_LDJ::UpgradeCost()
{
}

void AFlameThrowerTrap_LDJ::UpgradeAbility()
{
}

void AFlameThrowerTrap_LDJ::ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef)
{
	for (auto e : EnemyBoxRef)
	{
		auto temp = Cast<AZombieBase_KJY>(e);
		if (temp)
		{
			temp->Damage();
		}
	}
	GetWorld()->GetTimerManager().SetTimer(THandle, FTimerDelegate::CreateLambda([&]
	{
		// FireFX1->SetVisibility(true);
		// FireFX2->SetVisibility(true);
		// FireFX3->SetVisibility(true);
		// FireFX4->SetVisibility(true);
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
		{
			// FireFX1->SetVisibility(false);
			// FireFX2->SetVisibility(false);
			// FireFX3->SetVisibility(false);
			// FireFX4->SetVisibility(false);
			GetWorldTimerManager().ClearTimer(Handle);
		}), 3, false);
		GetWorldTimerManager().ClearTimer(THandle);
	}), 0.1, false);
}
