// zombie must die


#include "ZMDGameStateBase_LDJ.h"

void AZMDGameStateBase_LDJ::GameJudge()
{
	if (Life == 0)
	{
		UE_LOG(LogTemp,Warning, TEXT("YOU LOSE"));
	}
}
