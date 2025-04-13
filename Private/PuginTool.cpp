// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuginTool.h"
#include "PuginToolStyle.h"
#include "PuginToolCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "PuginTool/ToolUI.h"

static const FName PuginToolTabName("PuginTool");

#define LOCTEXT_NAMESPACE "FPuginToolModule"

void FPuginToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPuginToolStyle::Initialize();
	FPuginToolStyle::ReloadTextures();

	FPuginToolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPuginToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPuginToolModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPuginToolModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PuginToolTabName, FOnSpawnTab::CreateRaw(this, &FPuginToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPuginToolTabTitle", "PuginTool"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPuginToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPuginToolStyle::Shutdown();

	FPuginToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PuginToolTabName);
}

TSharedRef<SDockTab> FPuginToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPuginToolModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PuginTool.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(ToolUI)
			
		];
} //a

void FPuginToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(PuginToolTabName);
}

void FPuginToolModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FPuginToolCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FPuginToolCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPuginToolModule, PuginTool)