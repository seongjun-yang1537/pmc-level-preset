#pragma once

#include "CoreMinimal.h"

struct FLevelPresetData;

typedef TSharedPtr<FLevelPresetData> FLevelPresetDataPtr;

class FLevelPresetToolbar
{
public:
	void Construct(FToolBarBuilder& Builder);

private:
	TSharedPtr<SComboBox<FLevelPresetDataPtr>> LevelDropDown;
	
	TArray<FLevelPresetDataPtr> LevelPresets;
	FLevelPresetDataPtr SeletedLevelPreset;

	void OnAddLevelPreset();
	
	void OnButtonClicked();
	TSharedRef<SWidget> OnGenerateDropDownElement(FLevelPresetDataPtr Element);
	void OnSelectLevelPreset(FLevelPresetDataPtr NewElement, ESelectInfo::Type SelectInfo);
};
