// zombie must die


#include "PlayerBaseComp.h"

#include "PlayerBase_YMH.h"

UPlayerBaseComp::UPlayerBaseComp()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UPlayerBaseComp::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerBaseComp::InitializeComponent()
{
	Super::InitializeComponent();

	player = Cast<APlayerBase_YMH>(GetOwner());
	player->OnSetupInputDelegate.AddUObject(this, &UPlayerBaseComp::SetupPlayerInput);
}

void UPlayerBaseComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerBaseComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
}

