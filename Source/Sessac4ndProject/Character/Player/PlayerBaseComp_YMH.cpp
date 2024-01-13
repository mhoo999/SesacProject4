// zombie must die


#include "PlayerBaseComp_YMH.h"

#include "PlayerBase_YMH.h"

UPlayerBaseComp_YMH::UPlayerBaseComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UPlayerBaseComp_YMH::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerBaseComp_YMH::InitializeComponent()
{
	Super::InitializeComponent();

	player = Cast<APlayerBase_YMH>(GetOwner());
	player->OnSetupInputDelegate.AddUObject(this, &UPlayerBaseComp_YMH::SetupPlayerInput);
}

void UPlayerBaseComp_YMH::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerBaseComp_YMH::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
}

