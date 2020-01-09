// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#if WITH_EDITOR
#include "IDetailCustomization.h"
#include "PropertyCustomizationHelpers.h"
#endif

#if WITH_EDITOR

class FAttributeNameDetailsViewCustomizations : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** Begin IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	/** End IPropertyTypeCustomization interface */

private:
	void SetAttributesNameList(TArray<TSharedPtr<FString>>& InAttributesNameList);
	TSharedRef<IPropertyHandle> GetAttributeNameProperty();
	FText GetAttributeName() const;
	void OnAttributeSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo);

	TArray<TSharedPtr<FString>>AttributesNameList;
	TSharedPtr<IPropertyHandle> AttributePropertyHandle;

};

#endif
