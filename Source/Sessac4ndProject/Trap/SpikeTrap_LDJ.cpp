// zombie must die


#include "SpikeTrap_LDJ.h"


ASpikeTrap_LDJ::ASpikeTrap_LDJ()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpikeMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spike Mesh Component"));
	SpikeMeshComp->SetupAttachment(TileMesh);
	SpikeMeshComp->SetRelativeLocation(FVector(0,0,-50));
	
}

void ASpikeTrap_LDJ::BeginPlay()
{
	Super::BeginPlay();
}

void ASpikeTrap_LDJ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpikeTrap_LDJ::UpgradeCost()
{
	
}

void ASpikeTrap_LDJ::UpgradeAbility()
{
	
}

void ASpikeTrap_LDJ::ReactTrap()
{
	UE_LOG(LogTemp,Warning, TEXT("Child Trap"));
	// TO DO : 올렸다가 다시 내려가기
	GetWorld()->GetTimerManager().SetTimer(THandle, FTimerDelegate::CreateLambda([this]()->void
	{
		auto Temp = FMath::Lerp(SpikeMeshComp->GetComponentLocation().Z, 0, GetWorld()->GetDeltaSeconds()*10);
		UE_LOG(LogTemp,Warning, TEXT("123"));
		SpikeMeshComp->SetRelativeLocation(FVector(0,0,Temp));
	}), GetWorld()->GetDeltaSeconds(), true);
}
