// Copyright Epic Games, Inc. All Rights Reserved.

#include "TextureSetToMatCommands.h"

#define LOCTEXT_NAMESPACE "FTextureSetToMatModule"

void FTextureSetToMatCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "TextureSetToMat", "Execute TextureSetToMat action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
