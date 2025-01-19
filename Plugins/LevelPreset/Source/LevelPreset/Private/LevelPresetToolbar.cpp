#include "LevelPresetToolbar.h"

void FLevelPresetToolbar::Construct(FToolBarBuilder& Builder)
{
	SeletedLevelPreset = MakeShared<TPair<FString, FString>>(TEXT("None"), TEXT("None"));

	Builder.AddWidget(
		SNew(SComboBox<LevelPresetElement>)
		.OptionsSource(&LevelPresets)
		.OnGenerateWidget_Raw(this, &FLevelPresetToolbar::OnGenerateDropDownElement)
		[
			SNew(STextBlock)
				.Text_Lambda([this](){return FText::FromString(SeletedLevelPreset->Key);})
		]
	);

	Builder.AddWidget(
		SNew(SButton)
		.Text(FText::FromString(TEXT("+")))
	);

	Builder.AddWidget(
		SNew(SButton)
		.Text(FText::FromString(TEXT("Go")))
	);
}

TSharedRef<SWidget> FLevelPresetToolbar::OnGenerateDropDownElement(LevelPresetElement Element)
{
	return SNew(STextBlock)
		.Text(FText::FromString(Element->Key));
}

void FLevelPresetToolbar::OnButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked"));
}