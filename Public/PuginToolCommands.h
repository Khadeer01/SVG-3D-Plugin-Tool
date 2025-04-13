// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PuginToolStyle.h"

class FPuginToolCommands : public TCommands<FPuginToolCommands>
{
public:

	FPuginToolCommands()
		: TCommands<FPuginToolCommands>(TEXT("PuginTool"), NSLOCTEXT("Contexts", "PuginTool", "PuginTool Plugin"), NAME_None, FPuginToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};