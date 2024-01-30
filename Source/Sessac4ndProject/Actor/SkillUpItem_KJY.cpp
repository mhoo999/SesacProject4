// zombie must die


#include "Actor/SkillUpItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/TrapAndWeaponLevelUI_LDJ.h"

void ASkillUpItem_KJY::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SkillUpItemDropSound, GetActorLocation());
}

void ASkillUpItem_KJY::ReactItem()
{
	if (Player->IsLocallyControlled())
	{
		Player->skillPoint+=1;
	}
	auto MyPlayerController = Cast<APlayerController_YMH>(GetWorld()->GetFirstPlayerController());
	MyPlayerController->mainUI->WBP_TrapLevel->LevelUpUI();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SkillUpItemEatSound, GetActorLocation());
}
