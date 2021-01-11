// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SR_EditorStyle.h"

class FSR_EditorCommands : public TCommands<FSR_EditorCommands>
{
public:

	FSR_EditorCommands()
		: TCommands<FSR_EditorCommands>(TEXT("SR_Editor"), NSLOCTEXT("Contexts", "SR_Editor", "SR_Editor Plugin"), NAME_None, FSR_EditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};