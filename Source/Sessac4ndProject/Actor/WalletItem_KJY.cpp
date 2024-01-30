// zombie must die


#include "Actor/WalletItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/MoneyWidget_LDJ.h"

void AWalletItem_KJY::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), GoldItemDropSound, GetActorLocation());
}

void AWalletItem_KJY::ReactItem()
{
	if (Player->IsLocallyControlled())
	{
		Player->wallet+=50;
	}
	auto MyPlayerController = Cast<APlayerController_YMH>(GetWorld()->GetFirstPlayerController());
	MyPlayerController->mainUI->WBP_Money->SetMoneyText(Player->wallet);
}
