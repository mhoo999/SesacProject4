// zombie must die


#include "Trap/FreezeTrap_LDJ.h"

#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/Zombie_KJY.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Character/Player/PlayerUpgradeComp_YMH.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AFreezeTrap_LDJ::AFreezeTrap_LDJ()
{
	FreezeFX1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh1"));
	FreezeFX1->SetupAttachment(TileMesh);
	FreezeFX1->SetRelativeRotation(FRotator(90,0,0));
	FreezeFX1->SetRelativeLocation((FVector(30,-30,0)));
	FreezeFX1->SetVisibility(false);
	
	FreezeFX2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh2"));
	FreezeFX2->SetupAttachment(TileMesh);
	FreezeFX2->SetRelativeRotation(FRotator(90,0,0));
	FreezeFX2->SetRelativeLocation((FVector(30,30,0)));
	FreezeFX2->SetVisibility(false);
	
	FreezeFX3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh3"));
	FreezeFX3->SetupAttachment(TileMesh);
	FreezeFX3->SetRelativeRotation(FRotator(90,0,0));
	FreezeFX3->SetRelativeLocation((FVector(-30,-30,0)));
	FreezeFX3->SetVisibility(false);
	
	
	FreezeFX4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX Mesh4"));
	FreezeFX4->SetupAttachment(TileMesh);
	FreezeFX4->SetRelativeRotation(FRotator(90,0,0));
	FreezeFX4->SetRelativeLocation((FVector(-30,30,0)));
	FreezeFX4->SetVisibility(false);
} 

void AFreezeTrap_LDJ::BeginPlay()
{
	Super::BeginPlay();
	TrapLevel = PlayerUpgradeComp->FreezeTrapLevel;
}

void AFreezeTrap_LDJ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 AFreezeTrap_LDJ::GetCost()
{
	return this->Cost;
}

void AFreezeTrap_LDJ::UpgradeAbility()
{
}

void AFreezeTrap_LDJ::ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef)
{
	for (auto e : EnemyBoxRef)
	{
		e->GetCharacterMovement()->MaxWalkSpeed = (200 - 60 * TrapLevel);
	}
	GetWorld()->GetTimerManager().SetTimer(THandle, FTimerDelegate::CreateLambda([&]
	{
		FreezeFX1->SetVisibility(true);
		FreezeFX2->SetVisibility(true);
		FreezeFX3->SetVisibility(true);
		FreezeFX4->SetVisibility(true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReactFreezeTrapSound, GetActorLocation());
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
		{
			FreezeFX1->SetVisibility(false);
			FreezeFX2->SetVisibility(false);
			FreezeFX3->SetVisibility(false);
			FreezeFX4->SetVisibility(false);
			GetWorldTimerManager().ClearTimer(Handle);
		}), 3, false);
		GetWorldTimerManager().ClearTimer(THandle);
	}), 0.1, false);
}
