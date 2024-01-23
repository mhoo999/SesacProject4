// zombie must die


#include "CharacterBase_YMH.h"

ACharacterBase_YMH::ACharacterBase_YMH()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeScale3D(FVector(0.6f));
}

void ACharacterBase_YMH::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase_YMH::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase_YMH::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}