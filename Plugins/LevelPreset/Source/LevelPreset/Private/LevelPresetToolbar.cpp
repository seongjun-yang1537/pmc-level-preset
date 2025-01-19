#include "LevelPresetToolbar.h"

#include "FileHelpers.h"
#include "LevelPresetData.h"
#include "Kismet/GameplayStatics.h"

void FLevelPresetToolbar::Construct(FToolBarBuilder& Builder)
{
	SeletedLevelPreset = MakeShareable(new FLevelPresetData(TEXT("None"), TEXT("None")));

	Builder.AddSeparator();
	
	Builder.AddWidget(
		SAssignNew(LevelDropDown, SComboBox<FLevelPresetDataPtr>)
		.OptionsSource(&LevelPresets)
		.OnGenerateWidget_Raw(this, &FLevelPresetToolbar::OnGenerateDropDownElement)
		.OnSelectionChanged_Raw(this, &FLevelPresetToolbar::OnSelectLevelPreset)
		[
			SNew(STextBlock)
				.Text_Lambda([this](){return FText::FromString(SeletedLevelPreset->Prefix);})
		]
	);

	// Add Level Preset Button
	Builder.AddToolBarButton(
	FUIAction(
			FExecuteAction::CreateRaw(this, &FLevelPresetToolbar::OnAddLevelPreset)
		),
		NAME_None,
		FText::FromString("Add Level Preset Button"),
		FText::FromString("Click to Add Level Preset"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "PListEditor.Button_AddToArray"),
		EUserInterfaceActionType::Button // 인터페이스 동작 유형
	);

	// Load Level Preset Button
	Builder.AddToolBarButton(
	FUIAction(
		FExecuteAction::CreateRaw(this, &FLevelPresetToolbar::OnOpenLevelPreset)
		),
		NAME_None,
		FText::FromString("Load Level Preset Button"),
		FText::FromString("Click to Load Level Preset"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.ImportScene"),
		EUserInterfaceActionType::Button // 인터페이스 동작 유형
	);
}

#pragma region Private
void FLevelPresetToolbar::OnAddLevelPreset()
{
	if(!GEditor)
	{
		return;
	}

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if(!World)
	{
		return;
	}
	ULevel* Level = World->GetCurrentLevel();
	if(!Level)
	{
		return;
	}
	FString LevelName = Level->GetWorld()->GetName();
	FString LevelPath = Level->GetPathName();

	FLevelPresetDataPtr Ptr = MakeShareable(new FLevelPresetData(LevelName, LevelPath));

	auto ItrFinded =LevelPresets.FindByPredicate([Ptr](const FLevelPresetDataPtr& x)
	{
		return *x == *Ptr;
	});
	if(ItrFinded)
	{
		int32 index = LevelPresets.IndexOfByKey(*ItrFinded);
		LevelPresets.RemoveAt(index);
	}

	LevelPresets.Insert(Ptr, 0);
	SeletedLevelPreset = Ptr;
	LevelDropDown->RefreshOptions();
}

TSharedRef<SWidget> FLevelPresetToolbar::OnGenerateDropDownElement(FLevelPresetDataPtr Element)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(FText::FromString(Element->Prefix))
			.ToolTip(
				SNew(SToolTip).Text(FText::FromString(Element->LevelPath)))
		]
		+ SHorizontalBox::Slot()
		[
			SNew(SSpacer)
		]
		+SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(FText::FromString(Element->LevelPath))
			.ColorAndOpacity(FLinearColor::Gray.CopyWithNewOpacity(0.2f))
		];
}

void FLevelPresetToolbar::OnSelectLevelPreset(FLevelPresetDataPtr NewElement, ESelectInfo::Type SelectInfo)
{
	SeletedLevelPreset = NewElement;
}

void FLevelPresetToolbar::OnOpenLevelPreset()
{
	FEditorFileUtils::LoadMap(*SeletedLevelPreset->LevelPath);
}
#pragma endregion