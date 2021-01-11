// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TextureSetToMatStyle.h"

class FTextureSetToMatCommands : public TCommands<FTextureSetToMatCommands>
{
public:

	FTextureSetToMatCommands()
		: TCommands<FTextureSetToMatCommands>(TEXT("TextureSetToMat"), NSLOCTEXT("Contexts", "TextureSetToMat", "TextureSetToMat Plugin"), NAME_None, FTextureSetToMatStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
