// zombie must die


#include "Actor/SkillUpItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "PlayerController/PlayerController_YMH.h"
#include "UI/MainUI_YMH.h"
#include "UI/TrapAndWeaponLevelUI_LDJ.h"

void ASkillUpItem_KJY::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Monney : %s"), *GetActorLocation().ToString());
}

void ASkillUpItem_KJY::ReactItem()
{
	Player->skillPoint+=1;
	auto MyPlayerController = Cast<APlayerController_YMH>(GetWorld()->GetFirstPlayerController());
	MyPlayerController->mainUI->WBP_TrapLevel->LevelUpUI();
}
