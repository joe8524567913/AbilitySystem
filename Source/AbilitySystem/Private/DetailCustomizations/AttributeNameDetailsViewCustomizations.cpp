// Created by: ChengXinYuan
// Release year:2020.1

#include "DetailCustomizations/AttributeNameDetailsViewCustomizations.h"
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

#define LOCTEXT_NAMESPACE "AttributeNameDetailsViewCustomizations"

TSharedRef<IPropertyTypeCustomization> FAttributeNameDetailsViewCustomizations::MakeInstance()
{
	return MakeShareable(new FAttributeNameDetailsViewCustomizations());
}

void FAttributeNameDetailsViewCustomizations::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow & HeaderRow, IPropertyTypeCustomizationUtils & CustomizationUtils)
{
	SetAttributesNameList(AttributesNameList);
	AttributePropertyHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAttributeName, Attribute));
	if (AttributePropertyHandle.IsValid())
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
					.Text(this, &FAttributeNameDetailsViewCustomizations::GetAttributeName)
				]
			];
	}
}

void FAttributeNameDetailsViewCustomizations::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder & StructBuilder, IPropertyTypeCustomizationUtils & StructCustomizationUtils)
{
	FName AttributeName;
	GetAttributeNameProperty()->GetValue(AttributeName);
	FString* AttributeNamePtr = new FString(*AttributeName.ToString());

	StructBuilder.AddCustomRow(LOCTEXT("Attribute_DisplayName", "Attribute"))
		.ValueContent()
		[
			SNew(STextComboBox)
			.OptionsSource(&AttributesNameList)
			.OnSelectionChanged(this, &FAttributeNameDetailsViewCustomizations::OnAttributeSelected)
			.InitiallySelectedItem(MakeShareable(AttributeNamePtr))
		];

}

void FAttributeNameDetailsViewCustomizations::SetAttributesNameList(TArray<TSharedPtr<FString>>& InAttributesNameList)
{
	InAttributesNameList.Empty();
	UAbilitySettings* Settings = GetMutableDefault<UAbilitySettings>();
	if (!Settings)
	{
		InAttributesNameList.Add(MakeShared<FString>(FString(TEXT("AbilitySettings is none"))));
		return;
	}
	TSubclassOf<UAbilityBlackBoard> AbilityBlackBoardTemplate = Settings->AbilityBlackBoardTemplate;
	if (!AbilityBlackBoardTemplate)
	{
		InAttributesNameList.Add(MakeShared<FString>(FString(TEXT("AbilityBlackboard template is none"))));
		return;
	}
	UAbilityBlackBoard* AbilityBlackBoard = AbilityBlackBoardTemplate->GetDefaultObject<UAbilityBlackBoard>();
	if (!AbilityBlackBoard)
	{
		InAttributesNameList.Add(MakeShared<FString>(FString(TEXT("AbilityBlackboard template is none"))));
		return;
	}
	TMap<FName, FAttributes>Attributes = AbilityBlackBoard->GetAttributesList();
	for (TPair<FName, FAttributes> Value : Attributes)
	{
		InAttributesNameList.Add(MakeShared<FString>(Value.Key.ToString()));
	}
	if (!InAttributesNameList.Num())
	{
		InAttributesNameList.Add(MakeShared<FString>(FString(TEXT("AbilityBlackboard has no attributes"))));
	}
}

TSharedRef<IPropertyHandle> FAttributeNameDetailsViewCustomizations::GetAttributeNameProperty()
{
	return AttributePropertyHandle.ToSharedRef();
}

FText FAttributeNameDetailsViewCustomizations::GetAttributeName() const
{
	return FText::FromString(TEXT("Attribute"));
}

void FAttributeNameDetailsViewCustomizations::OnAttributeSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo)
{
	if (ItemSlected.IsValid())
	{
		FName AttributeName = **ItemSlected;
		GetAttributeNameProperty()->SetValue(AttributeName);
	}

}

#undef LOCTEXT_NAMESPACE

#endif
