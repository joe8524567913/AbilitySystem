// Created by: ChengXinYuan
// Release year:2020.1


#include "DetailCustomizations/EffectInfoDetailsViewCustomizations.h"
#if WITH_EDITOR
#include "IDetailChildrenBuilder.h"
#include "IDetailGroup.h"
#endif
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Ability/AbilityBlackBoard.h"
#include "Settings/AbilitySettings.h"
#include "Ability/TaskBase.h"

#if WITH_EDITOR

#define LOCTEXT_NAMESPACE "EffectInfoDetailsViewCustomizations"


TSharedRef<IPropertyTypeCustomization> FEffectInfoDetailsViewCustomizations::MakeInstance()
{
	return MakeShareable(new FEffectInfoDetailsViewCustomizations());
}

void FEffectInfoDetailsViewCustomizations::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow & HeaderRow, IPropertyTypeCustomizationUtils & CustomizationUtils)
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
				.Text(this, &FEffectInfoDetailsViewCustomizations::GetEffectInfoName)
			]
		];
}

void FEffectInfoDetailsViewCustomizations::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder & StructBuilder, IPropertyTypeCustomizationUtils & StructCustomizationUtils)
{
	EffectSlotPropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectInfo, EffectSlot));
	TSharedPtr<IPropertyHandle> EffectClassPropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectInfo, EffectClass));
	TSharedPtr<IPropertyHandle> LifePropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectInfo, Life));
	IntervalTypePropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectInfo, ActivateType));
	IntervalTimePropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectInfo, IntervalTime));
	IntervalTimesPropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectInfo, TimePoints));

	//FSimpleDelegate OnIntervalTypeChanged = FSimpleDelegate::CreateSP(this, &FEffectInfoDetailsViewCustomizations::OnIntervalTypeChanged);
	//IntervalTypePropertyHandle->SetOnPropertyValueChanged(OnIntervalTypeChanged);

	SetEffectSlotNameList(EffectSlotNameList);

	FName EffectSlotName;
	GetEffectSlotNameProperty()->GetValue(EffectSlotName);
	FString* EffectSlotNamePtr = new FString(*EffectSlotName.ToString());

	StructBuilder.AddCustomRow(LOCTEXT("EffectInfo_DisplayName", "EffectInfo"))
		.ValueContent()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4)
			[
				SNew(STextComboBox)
				.OptionsSource(&EffectSlotNameList)
				.OnSelectionChanged(this, &FEffectInfoDetailsViewCustomizations::OnEffectSlotSelected)
				.InitiallySelectedItem(MakeShareable(EffectSlotNamePtr))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4)
			[
				EffectClassPropertyHandle->CreatePropertyValueWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4)
			[
				LifePropertyHandle->CreatePropertyValueWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4)
			[
				IntervalTypePropertyHandle->CreatePropertyValueWidget()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4)
			[
				SAssignNew(IntervalTimeOverlay,SOverlay)
				+SOverlay::Slot()
				[
					IntervalTimePropertyHandle->CreatePropertyValueWidget()
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4)
			[
				SAssignNew(IntervalTimesOverlay, SOverlay)				
			]
		];
	InitIntervalType();
}

void FEffectInfoDetailsViewCustomizations::OnEffectSlotSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo)
{
	if (ItemSlected.IsValid())
	{
		FName EffectSlotName = **ItemSlected;
		EffectSlotPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectSlot, SlotName))->SetValue(EffectSlotName);
	}
}

TSharedRef<IPropertyHandle> FEffectInfoDetailsViewCustomizations::GetEffectSlotNameProperty()
{
	return EffectSlotPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FEffectSlot, SlotName)).ToSharedRef();
}

FText FEffectInfoDetailsViewCustomizations::GetEffectInfoName() const
{
	return FText::FromString(TEXT("EffectInfo"));
}

void FEffectInfoDetailsViewCustomizations::InitIntervalType()
{
	bool bTimePoints;
	IntervalTypePropertyHandle->GetValue(bTimePoints);
	if (bTimePoints)
	{
		IntervalTimeOverlay->ClearChildren();
		IntervalTimesOverlay->AddSlot()
			[
				IntervalTimesPropertyHandle->CreatePropertyValueWidget()
			];
	}
	else
	{
		IntervalTimesOverlay->ClearChildren();
		IntervalTimeOverlay->AddSlot()
			[
				IntervalTimePropertyHandle->CreatePropertyValueWidget()
			];
	}
}

void FEffectInfoDetailsViewCustomizations::OnIntervalTypeChanged()
{
	InitIntervalType();
}

#undef LOCTEXT_NAMESPACE


#endif