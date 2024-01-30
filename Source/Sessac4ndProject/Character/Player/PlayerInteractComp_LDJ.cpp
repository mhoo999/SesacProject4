// zombie must die


#include "Character/Player/PlayerInteractComp_LDJ.h"

#include "PlayerBase_YMH.h"
#include "PlayerFireComp_YMH.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/ZombieBase_KJY.h"
#include "Kismet/GameplayStatics.h"
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
	EndVec = StartVec + Player->FollowCamera->GetForwardVector() * Player->FireComp->attackDistance;
	params.AddIgnoredActor(GetOwner());
	FHitResult HitInfo;
	auto bHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(),StartVec,EndVec,20.0f,TraceTypeQuery1, false, ToIgnore, EDrawDebugTrace::None, HitInfo,true);
	// auto bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartVec, EndVec, ECC_Visibility, params);
	// DrawDebugLine(GetWorld(), StartVec, EndVec, FColor::Purple);
	if (bHit)
	{
		ServerRPC_InteractionTrace(HitInfo);
	}
}

void UPlayerInteractComp_LDJ::ServerRPC_InteractionTrace_Implementation(FHitResult HitInfo)
{
	auto HitActor = HitInfo.GetActor();
	auto Zombie = Cast<AZombieBase_KJY>(HitActor);
	ClientRPC_InteractionTrace(Zombie);
}

void UPlayerInteractComp_LDJ::ClientRPC_InteractionTrace_Implementation(AZombieBase_KJY* Zombie)
{
	if (!Zombie)
	{
		MyPC->mainUI->WBP_ZombieHPUI_LDJ->ClearZombieHPUI();
		return;
	}
	if (Player->IsLocallyControlled())
	{
		MyPC->mainUI->WBP_ZombieHPUI_LDJ->ShowZombieHPUI(Zombie->CurrentHp, Zombie->MaxHp, Zombie);
	}
}


