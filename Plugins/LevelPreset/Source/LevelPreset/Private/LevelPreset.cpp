// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelPreset.h"

#include "LevelEditor.h"
#include "LevelPresetToolbar.h"

#define LOCTEXT_NAMESPACE "FLevelPresetModule"

void FLevelPresetModule::StartupModule()
{
	ToolbarProxy = MakeUnique<FLevelPresetToolbar>();
	
	ToolbarExtender = MakeShared<FExtender>();
	ToolbarExtender->AddToolBarExtension(
		"ProjectSettings",
		EExtensionHook::Before,
		nullptr,
		FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder)
		{
			if(ToolbarProxy.IsValid())
			{
				ToolbarProxy->Construct(Builder);
			}
		}));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FLevelPresetModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLevelPresetModule, LevelPreset)