// Created by: ChengXinYuan
// Release year:2020.1

#pragma once
#include "CoreMinimal.h"
#if WITH_EDITOR
#include "Editor/GraphEditor/Public/SGraphPin.h"
#include "UnrealEd/Public/EdGraphUtilities.h"
#endif

class UAbilityBlackBoard;

#if WITH_EDITOR

class SAttributeNamePin:public SGraphPin
{
	SLATE_BEGIN_ARGS(SAttributeNamePin) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
	void OnAttributeSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo);
	virtual TSharedRef<SWidget>	GetDefaultValueWidget()override;

private:
	void SetAttributesNameList(TArray<TSharedPtr<FString>>& InAttributesNameList);


private:
	TArray<TSharedPtr<FString>>AttributesNameList;
};

class FAtributeNameGraphPanelPinFactory :public FGraphPanelPinFactory
{
public:
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;
};

#endif