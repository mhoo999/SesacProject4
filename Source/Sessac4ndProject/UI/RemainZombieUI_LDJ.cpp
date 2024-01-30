// zombie must die


#include "UI/RemainZombieUI_LDJ.h"

#include "Components/TextBlock.h"

void URemainZombieUI_LDJ::SetRemainZombie(int32 RemainZombies)
{
	Txt_RemainZombie->SetText(FText().AsNumber(RemainZombies));
}
