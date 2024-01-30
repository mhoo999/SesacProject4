// zombie must die


#include "SpikeTrap_LDJ.h"

#include "Character/Enemy/ZombieAnim.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "Character/Enemy/ZombieFSM.h"
#include "Character/Enemy/Zombie_KJY.h"
#include "Character/Player/PlayerBuildComp_LDJ.h"
#include "Character/Player/PlayerUpgradeComp_YMH.h"
#include "Kismet/GameplayStatics.h"


ASpikeTrap_LDJ::ASpikeTrap_LDJ()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpikeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spike Mesh Component"));
	SpikeMeshComp->SetupAttachment(TileMesh);
	SpikeMeshComp->SetRelativeScale3D(FVector(1.25));

	SpikeMeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spike Mesh Component2"));
	SpikeMeshComp2->SetupAttachment(TileMesh);
	SpikeMeshComp2->SetRelativeScale3D(FVector(1.25));

	SpikeMeshComp2->SetVisibility(false);
}

void ASpikeTrap_LDJ::BeginPlay()
{
	Super::BeginPlay();
	TrapLevel = PlayerUpgradeComp->SpikeTrapLevel;
}

void ASpikeTrap_LDJ::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 ASpikeTrap_LDJ::GetCost()
{
	return this->Cost;
}

void ASpikeTrap_LDJ::UpgradeAbility()
{
	
}

void ASpikeTrap_LDJ::ReactTrap(TArray<AZombieBase_KJY*> EnemyBoxRef)
{
	for (auto e : EnemyBoxRef)
	{
		auto temp = Cast<AZombieBase_KJY>(e);
		if (temp)
		{
			temp->ServerRPCDamage(TrapLevel);
			//널 에러가 뜬다면, 좀비베이스의 Die함수를 Timer로 씌워서 2초 늦게 죽자.
		}
	}
		
	GetWorld()->GetTimerManager().SetTimer(THandle, FTimerDelegate::CreateLambda([&]
	{
		SpikeMeshComp->SetVisibility(false);
		SpikeMeshComp2->SetVisibility(true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReactSpikeTrapSound, GetActorLocation());
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
		{
			SpikeMeshComp->SetVisibility(true);
			SpikeMeshComp2->SetVisibility(false);
			GetWorldTimerManager().ClearTimer(Handle);
		}), 1, false);
		GetWorldTimerManager().ClearTimer(THandle);
	}), 0.1, false);
}

// void ASpikeTrap_LDJ::ReactTrap()
// {
// 	UE_LOG(LogTemp,Warning, TEXT("Child Trap"));
// 	// TO DO : 올렸다가 다시 내려가기
// 	GetWorld()->GetTimerManager().SetTimer(THandle, FTimerDelegate::CreateLambda([this]()->void
// 	{
// 		if (!GoalArrived)
// 		{
// 			auto Temp = FMath::Lerp(SpikeMeshComp->GetComponentLocation().Z, 0, GetWorld()->GetDeltaSeconds() * 10);
// 			SpikeMeshComp->SetRelativeLocation(FVector(0, 0, Temp));
// 			if (Temp > -0.1)
// 			{
// 				GoalArrived = true;
// 			}
// 		}
// 		else
// 		{
// 			auto Temp = FMath::Lerp(SpikeMeshComp->GetComponentLocation().Z, -50, GetWorld()->GetDeltaSeconds() * 10);
// 			SpikeMeshComp->SetRelativeLocation(FVector(0, 0, Temp));
// 			if (Temp < -49.9)
// 			{
// 				GoalArrived = false;
// 				GetWorld()->GetTimerManager().ClearTimer(THandle);
// 			}
// 		}
// 	}), GetWorld()->GetDeltaSeconds(), true);
// }
