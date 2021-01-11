// Copyright Epic Games, Inc. All Rights Reserved.

#include "SR_Editor.h"
#include "SR_EditorStyle.h"
#include "SR_EditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName SR_EditorTabName("SR_Editor");

#define LOCTEXT_NAMESPACE "FSR_EditorModule"

void FSR_EditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSR_EditorStyle::Initialize();
	FSR_EditorStyle::ReloadTextures();

	FSR_EditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSR_EditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSR_EditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSR_EditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SR_EditorTabName, FOnSpawnTab::CreateRaw(this, &FSR_EditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSR_EditorTabTitle", "SR_Editor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FSR_EditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSR_EditorStyle::Shutdown();

	FSR_EditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SR_EditorTabName);
	//test for commit!
}

TSharedRef<SDockTab> FSR_EditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FSR_EditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("SR_Editor.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FSR_EditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(SR_EditorTabName);
}

void FSR_EditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FSR_EditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSR_EditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSR_EditorModule, SR_Editor)