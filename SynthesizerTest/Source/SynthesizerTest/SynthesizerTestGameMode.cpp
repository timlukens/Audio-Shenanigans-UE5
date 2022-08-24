// Copyright Epic Games, Inc. All Rights Reserved.

#include "SynthesizerTestGameMode.h"
#include "SynthesizerTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASynthesizerTestGameMode::ASynthesizerTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
