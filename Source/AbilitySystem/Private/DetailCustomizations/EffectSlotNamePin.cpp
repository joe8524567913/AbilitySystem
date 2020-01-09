// Created by: ChengXinYuan
// Release year:2020.1


#include "DetailCustomizations/EffectSlotNamePin.h"
#include "Widgets/Input/STextComboBox.h"
#if WITH_EDITOR
#include "BlueprintGraph/Classes/EdGraphSchema_K2.h"
#endif
#include "Settings/AbilitySettings.h"
#include "Ability/AbilityBlackBoard.h"

#if WITH_EDITOR

void SEffectSlotNamePin::Construct(const FArguments & InArgs, UEdGraphPin * InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InPin);

	SEffectSlotNamePinList.Empty();
	SetEffectSlotNameList();

}

void SEffectSlotNamePin::OnMontageSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo)
{
	if (!ItemSlected)
	{
		return;
	}
	FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();
	FString MontageAttributes = *ItemSlected.Get();
	if (CurrentDefaultValue.IsEmpty())
	{
		CurrentDefaultValue = FString(TEXT("()"));
	}
	FString MontageAttributeString = TEXT("(");
	if (!MontageAttributes.IsEmpty())
	{
		MontageAttributeString += TEXT("SlotName=\"");
		MontageAttributeString += MontageAttributes;
		MontageAttributeString += TEXT("\"");
	}
	MontageAttributeString += TEXT(")");
	if (!CurrentDefaultValue.Equals(MontageAttributeString))
	{
		GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, MontageAttributeString);
	}
}

TSharedRef<SWidget> SEffectSlotNamePin::GetDefaultValueWidget()
{
	FString* SelectedStringPtr = new FString(*GraphPinObj->GetDefaultAsString());
	return SNew(STextComboBox)
		.OptionsSource(&SEffectSlotNamePinList)
		.OnSelectionChanged(this, &SEffectSlotNamePin::OnMontageSelected)
		.InitiallySelectedItem(MakeShareable(SelectedStringPtr));
}

void SEffectSlotNamePin::SetEffectSlotNameList()
{
	UAbilitySettings* Settings = GetMutableDefault<UAbilitySettings>();
	UAbilityBlackBoard* AbilityBlackBoard = Settings->AbilityBlackBoardTemplate->GetDefaultObject<UAbilityBlackBoard>();
	TArray<FName>EffectSlots = AbilityBlackBoard->GetEffectSlotList();
	for (FName EffectSlotName : EffectSlots)
	{
		SEffectSlotNamePinList.Add(MakeShared<FString>(EffectSlotName.ToString()));
	}
}

TSharedPtr<class SGraphPin> FEffectSlotNameGraphPanelPinFactory::CreatePin(UEdGraphPin * InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	if (InPin->PinType.PinCategory == K2Schema->PC_Struct && InPin->PinType.PinSubCategoryObject == FEffectSlot::StaticStruct())
	{
		return SNew(SEffectSlotNamePin, InPin);
	}
	return nullptr;
}

#endif