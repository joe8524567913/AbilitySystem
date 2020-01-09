// Created by: ChengXinYuan
// Release year:2020.1


#include "DetailCustomizations/AttributeNamePin.h"
#include "Widgets/Input/STextComboBox.h"
#if WITH_EDITOR
#include "BlueprintGraph/Classes/EdGraphSchema_K2.h"
#endif
#include "Settings/AbilitySettings.h"
#include "Ability/AbilityBlackBoard.h"

#if WITH_EDITOR

void SAttributeNamePin::Construct(const FArguments & InArgs, UEdGraphPin * InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InPin);

	SetAttributesNameList(AttributesNameList);	
}

void SAttributeNamePin::OnAttributeSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo)
{
	if (!ItemSlected)
	{
		return;
	}
	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();
	FString Attributes = *ItemSlected.Get();
	if (CurrentDefaultValue.IsEmpty())
	{
		CurrentDefaultValue = FString(TEXT("()"));
	}
	FString AttributeString = TEXT("(");
	if (!Attributes.IsEmpty())
	{
		AttributeString += TEXT("Attribute=\"");
		AttributeString += Attributes;
		AttributeString += TEXT("\"");
	}
	AttributeString += TEXT(")");
	if (!CurrentDefaultValue.Equals(AttributeString))
	{
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, AttributeString);
	}
}

TSharedRef<SWidget> SAttributeNamePin::GetDefaultValueWidget()
{
	FString* SelectedStringPtr = new FString(*GraphPinObj->GetDefaultAsString());
	return SNew(STextComboBox)
		.OptionsSource(&AttributesNameList)
		.OnSelectionChanged(this, &SAttributeNamePin::OnAttributeSelected) 
		.InitiallySelectedItem(MakeShareable(SelectedStringPtr));
}

void SAttributeNamePin::SetAttributesNameList(TArray<TSharedPtr<FString>>& InAttributesNameList)
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

TSharedPtr<class SGraphPin> FAtributeNameGraphPanelPinFactory::CreatePin(UEdGraphPin * InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	if (InPin->PinType.PinCategory == K2Schema->PC_Struct && InPin->PinType.PinSubCategoryObject == FAttributeName::StaticStruct())
	{
		return SNew(SAttributeNamePin, InPin);
	}
	return nullptr;

}

#endif
