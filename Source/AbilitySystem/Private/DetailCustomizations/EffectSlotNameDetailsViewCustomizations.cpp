// Created by: ChengXinYuan
// Release year:2020.1


#include "DetailCustomizations/EffectSlotNameDetailsViewCustomizations.h"
#if WITH_EDITOR
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"
#endif
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Ability/AbilityBlackBoard.h"
#include "Settings/AbilitySettings.h"

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "EffectSlotNameDetailsViewCustomizations"

TSharedRef<IPropertyTypeCustomization> FEffectSlotNameDetailsViewCustomizations::MakeInstance()
{
	return MakeShareable(new FEffectSlotNameDetailsViewCustomizations());
}

void FEffectSlotNameDetailsViewCustomizations::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow & HeaderRow, IPropertyTypeCustomizationUtils & CustomizationUtils)
{
	SetEffectSlotNameList(EffectSlotNameList);
	EffectSlotPropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectSlot, SlotName));
	if (EffectSlotPropertyHandle.IsValid())
	{
		HeaderRow
			.NameContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Font(FEditorStyle::GetFontStyle("PropertyWindow.NormalFont"))
					.Text(this, &FEffectSlotNameDetailsViewCustomizations::GetEffectSlotName)
				]
			];
	}
}

void FEffectSlotNameDetailsViewCustomizations::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder & StructBuilder, IPropertyTypeCustomizationUtils & StructCustomizationUtils)
{
	FName EffectSlotName;
	GetEffectSlotNameProperty()->GetValue(EffectSlotName);
	FString* EffectSlotNamePtr = new FString(*EffectSlotName.ToString());

	StructBuilder.AddCustomRow(LOCTEXT("EffectSlot_DisplayName", "EffectSlot"))
		.ValueContent()
		[
			SNew(STextComboBox)
			.OptionsSource(&EffectSlotNameList)
			.OnSelectionChanged(this, &FEffectSlotNameDetailsViewCustomizations::OnEffectSlotSelected)
			.InitiallySelectedItem(MakeShareable(EffectSlotNamePtr))
		];

}

void FEffectSlotNameDetailsViewCustomizations::SetEffectSlotNameList(TArray<TSharedPtr<FString>>& InEffectSlotNameList)
{
	InEffectSlotNameList.Empty();
	UAbilitySettings* Settings = GetMutableDefault<UAbilitySettings>();
	if (!Settings)
	{
		InEffectSlotNameList.Add(MakeShared<FString>(FString(TEXT("AbilitySettings is none"))));
		return;
	}
	TSubclassOf<UAbilityBlackBoard> AbilityBlackBoardTemplate = Settings->AbilityBlackBoardTemplate;
	if (!AbilityBlackBoardTemplate)
	{
		InEffectSlotNameList.Add(MakeShared<FString>(FString(TEXT("AbilityBlackboard template is none"))));
		return;
	}
	UAbilityBlackBoard* AbilityBlackBoard = AbilityBlackBoardTemplate->GetDefaultObject<UAbilityBlackBoard>();
	if (!AbilityBlackBoard)
	{
		InEffectSlotNameList.Add(MakeShared<FString>(FString(TEXT("AbilityBlackboard template is none"))));
		return;
	}
	TArray<FName>EffectSlotNames = AbilityBlackBoard->GetEffectSlotList();
	for (FName EffectSlotName : EffectSlotNames)
	{
		InEffectSlotNameList.Add(MakeShared<FString>(EffectSlotName.ToString()));
	}
	if (!InEffectSlotNameList.Num())
	{
		InEffectSlotNameList.Add(MakeShared<FString>(FString(TEXT("AbilityBlackboard has no attributes"))));
	}
}

TSharedRef<IPropertyHandle> FEffectSlotNameDetailsViewCustomizations::GetEffectSlotNameProperty()
{
	return EffectSlotPropertyHandle.ToSharedRef();
}

FText FEffectSlotNameDetailsViewCustomizations::GetEffectSlotName() const
{
	return FText::FromString(TEXT("EffectSlot"));
}

void FEffectSlotNameDetailsViewCustomizations::OnEffectSlotSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo)
{
	if (ItemSlected.IsValid())
	{
		FName EffectSlotName = **ItemSlected;
		GetEffectSlotNameProperty()->SetValue(EffectSlotName);
	}

}

#undef LOCTEXT_NAMESPACE

#endif
