// zombie must die


#include "Actor/WalletItem_KJY.h"
#include "Character/Player/PlayerBase_YMH.h"

void AWalletItem_KJY::ReactItem()
{
	Player->wallet+=50;
}
