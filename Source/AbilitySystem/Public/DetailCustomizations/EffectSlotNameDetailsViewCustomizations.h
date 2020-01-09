// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#if WITH_EDITOR
#include "IDetailCustomization.h"
#include "PropertyCustomizationHelpers.h"
#endif

#if WITH_EDITOR

class FEffectSlotNameDetailsViewCustomizations : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** Begin IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	/** End IPropertyTypeCustomization interface */

protected:
	void SetEffectSlotNameList(TArray<TSharedPtr<FString>>& InEffectSlotNameList);
	virtual void OnEffectSlotSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo);
	virtual TSharedRef<IPropertyHandle> GetEffectSlotNameProperty();

private:
	FText GetEffectSlotName() const;

	TArray<TSharedPtr<FString>>EffectSlotNameList;
	TSharedPtr<IPropertyHandle> EffectSlotPropertyHandle;

};

#endif
