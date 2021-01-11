// Copyright Epic Games, Inc. All Rights Reserved.

#include "SR_EditorCommands.h"

#define LOCTEXT_NAMESPACE "FSR_EditorModule"

void FSR_EditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "SR_Editor", "Bring up SR_Editor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
