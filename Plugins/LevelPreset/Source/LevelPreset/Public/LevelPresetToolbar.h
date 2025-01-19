#pragma once

#include "CoreMinimal.h"

typedef TSharedPtr<TPair<FString, FString>> LevelPresetElement;

class FLevelPresetToolbar
{
public:
	void Construct(FToolBarBuilder& Builder);

private:
	TArray<LevelPresetElement> LevelPresets;
	LevelPresetElement SeletedLevelPreset;
	
	void OnButtonClicked();
	TSharedRef<SWidget> OnGenerateDropDownElement(LevelPresetElement Element);
};
