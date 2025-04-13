// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuginToolCommands.h"

#define LOCTEXT_NAMESPACE "FPuginToolModule"

void FPuginToolCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "PuginTool", "Bring up PuginTool window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
