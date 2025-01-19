#include "LevelPresetToolbar.h"

void FLevelPresetToolbar::Construct(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(
	FUIAction(FExecuteAction::CreateRaw(this, &FLevelPresetToolbar::OnButtonClicked)),
	NAME_None,
	FText::FromString("My Button"),
	FText::FromString("Click to do something!"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Settings") // 아이콘
	);
}

void FLevelPresetToolbar::OnButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked"));
}