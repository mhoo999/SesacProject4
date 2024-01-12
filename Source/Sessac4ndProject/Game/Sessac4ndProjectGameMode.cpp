// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sessac4ndProjectGameMode.h"
#include "Character/Sessac4ndProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASessac4ndProjectGameMode::ASessac4ndProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
