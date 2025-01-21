// Copyright Epic Games, Inc. All Rights Reserved.

#include "AINavigationGameMode.h"
#include "AINavigationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAINavigationGameMode::AAINavigationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
