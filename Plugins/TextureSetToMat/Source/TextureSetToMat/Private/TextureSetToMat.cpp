// Copyright Epic Games, Inc. All Rights Reserved.

#include "TextureSetToMat.h"
#include "TextureSetToMatStyle.h"
#include "TextureSetToMatCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName TextureSetToMatTabName("TextureSetToMat");

#define LOCTEXT_NAMESPACE "FTextureSetToMatModule"

void FTextureSetToMatModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTextureSetToMatStyle::Initialize();
	FTextureSetToMatStyle::ReloadTextures();

	FTextureSetToMatCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTextureSetToMatCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FTextureSetToMatModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTextureSetToMatModule::RegisterMenus));
}

void FTextureSetToMatModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTextureSetToMatStyle::Shutdown();

	FTextureSetToMatCommands::Unregister();
}

void FTextureSetToMatModule::PluginButtonClicked()
{
	
	//Material'/Game/BBB.BBB'

	/*测试父材质赋予贴图*/
	//SetMaterialTextureTest();

	/*测试多线程*/
	
	
}

void FTextureSetToMatModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTextureSetToMatCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTextureSetToMatCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

bool FTextureSetToMatModule::SetMaterialTextureTest()
{
	//Material'/Game/BBB.BBB'
	UObject* Obj = LoadObject<UObject>(nullptr, TEXT("Material'/Game/BBB.BBB'"));  
	UObject* ImgObj = LoadObject<UObject>(nullptr, TEXT("Texture2D'/Game/timg.timg'"));  

	if (Obj&&ImgObj)
	{
		UMaterialInterface* MatAsset = Cast<UMaterialInterface>(Obj);  
		UTexture2D* TextureAsset = Cast<UTexture2D>(ImgObj);
		MatAsset->GetMaterial()->SetTextureParameterValueEditorOnly(FName(TEXT("Texture")),TextureAsset);
		MatAsset->PostEditChange();
		MatAsset->MarkPackageDirty();

		return true;
	}
	
	return false;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTextureSetToMatModule, TextureSetToMat)