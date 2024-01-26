// zombie must die


#include "Character/Player/WaveStartComp_LDJ.h"

void UWaveStartComp_LDJ::BeginPlay()
{
	Super::BeginPlay();
}

void UWaveStartComp_LDJ::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWaveStartComp_LDJ::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
}
