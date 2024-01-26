// zombie must die


#include "Character/Player/UpgradeComp_YMH.h"

#include "EnhancedInputComponent.h"

UUpgradeComp_YMH::UUpgradeComp_YMH()
{
	PrimaryComponentTick.bCanEverTick = true;

	
	/*static ConstructorHelpers::FObjectFinder<UInputAction> IA_MouseModeRef(TEXT("/Game/LDJ/Input/IA_MouseMode.IA_MouseMode"));
	if (IA_MouseModeRef.Succeeded()) IA_MouseMode = IA_MouseModeRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LevelUpBtnRef(TEXT("/Game/LDJ/Input/IA_LevelUpBtn.IA_LevelUpBtn"));
	if (IA_LevelUpBtnRef.Succeeded()) IA_LevelUpBtn = IA_LevelUpBtnRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_WaveStartRef(TEXT("/Game/LDJ/Input/IA_WaveStart.IA_WaveStart"));
	if (IA_WaveStartRef.Succeeded()) IA_WaveStart = IA_WaveStartRef.Object;*/
}

void UUpgradeComp_YMH::BeginPlay()
{
	Super::BeginPlay();

	
}

void UUpgradeComp_YMH::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

/*void UUpgradeComp_YMH::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Trap Upgrade Input
		EnhancedInputComponent->BindAction(IA_ChooseTrap1, ETriggerEvent::Triggered, this,
								   &UUpgradeComp_YMH::UpgradeSpikeTrap);
		EnhancedInputComponent->BindAction(IA_MouseMode, ETriggerEvent::Started, this,
								   &UUpgradeComp_YMH::SetMouseMode);
		EnhancedInputComponent->BindAction(IA_MouseMode, ETriggerEvent::Completed, this,
						   &UUpgradeComp_YMH::SetMouseMode);
		EnhancedInputComponent->BindAction(IA_LevelUpBtn, ETriggerEvent::Started, this,
						   &UUpgradeComp_YMH::LevelUp);
		EnhancedInputComponent->BindAction(IA_WaveStart, ETriggerEvent::Started, this,
				   &UUpgradeComp_YMH::WaveStart);
	}
}*/

