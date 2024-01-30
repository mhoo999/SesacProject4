// zombie must die


#include "PlayerBaseComp_YMH.h"

#include "PlayerBase_YMH.h"
#include "PlayerController/PlayerController_YMH.h"

UPlayerBaseComp_YMH::UPlayerBaseComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UPlayerBaseComp_YMH::BeginPlay()
{
	Super::BeginPlay();
	player->wallet = 500;
}

void UPlayerBaseComp_YMH::InitializeComponent()
{
	Super::InitializeComponent();

	player = Cast<APlayerBase_YMH>(GetOwner());
	player->OnSetupInputDelegate.AddUObject(this, &UPlayerBaseComp_YMH::SetupPlayerInput);

	FTimerHandle initTimer;
	GetWorld()->GetTimerManager().SetTimer(initTimer, FTimerDelegate::CreateLambda([&]
	{
		PlayerController = Cast<APlayerController_YMH>(player->Controller);
	}), 0.2, false, 0.2);
}

void UPlayerBaseComp_YMH::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerBaseComp_YMH::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	
}

