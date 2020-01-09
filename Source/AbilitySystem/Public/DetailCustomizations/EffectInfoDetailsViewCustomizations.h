// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#if WITH_EDITOR
#include "DetailCustomizations/EffectSlotNameDetailsViewCustomizations.h"
#include "PropertyCustomizationHelpers.h"
#endif

#if WITH_EDITOR

class FEffectInfoDetailsViewCustomizations : public FEffectSlotNameDetailsViewCustomizations
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** Begin IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils);
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	/** End IPropertyTypeCustomization interface */

protected:
	virtual void OnEffectSlotSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo)override;
	virtual TSharedRef<IPropertyHandle> GetEffectSlotNameProperty()override;

private:
	FText GetEffectInfoName() const;
	void InitIntervalType();
	void OnIntervalTypeChanged();

	TArray<TSharedPtr<FString>>EffectSlotNameList;
	TSharedPtr<IPropertyHandle> EffectSlotPropertyHandle;
	TSharedPtr<IPropertyHandle> IntervalTypePropertyHandle;
	TSharedPtr<IPropertyHandle> IntervalTimePropertyHandle;
	TSharedPtr<IPropertyHandle> IntervalTimesPropertyHandle;

	TSharedPtr<SOverlay> IntervalTimeOverlay;
	TSharedPtr<SOverlay> IntervalTimesOverlay;
};

#endif
