// zombie must die


#include "Character/Player/PlayerInteractComp_LDJ.h"

#include "PlayerBase_YMH.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/ZombieHPUI_LDJ.h"

UPlayerInteractComp_LDJ::UPlayerInteractComp_LDJ()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInteractComp_LDJ::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerBase_YMH>(GetOwner());
	PC = GetWorld()->GetFirstPlayerController();
	MyPC = Cast<APlayerController_YMH>(PC);
}


void UPlayerInteractComp_LDJ::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InteractLineTrace();
}

void UPlayerInteractComp_LDJ::InteractLineTrace()
{
	StartVec = Player->FollowCamera->GetComponentLocation();
	EndVec = StartVec + Player->FollowCamera->GetForwardVector() * 10000;
	params.AddIgnoredActor(GetOwner());
	auto bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartVec, EndVec, ECC_Visibility, params);
	DrawDebugLine(GetWorld(), StartVec, EndVec, FColor::Purple);
	if (bHit)
	{
		auto temp = HitInfo.GetActor();
		BringZombieHPAndShowUI(temp);
	}
	
}

void UPlayerInteractComp_LDJ::BringZombieHPAndShowUI(AActor* HitActor)
{
	auto Zombie = Cast<AZombieBase_KJY>(HitActor);
	if (!Zombie)
	{
		MyPC->mainUI->WBP_ZombieHPUI_LDJ->ClearZombieHPUI();
		return;
	}

	if (Player->IsLocallyControlled())
	{
		MyPC->mainUI->WBP_ZombieHPUI_LDJ->ShowZombieHPUI(Zombie->CurrentHp, Zombie->MaxHp);
	}
	
}


