// Created by: ChengXinYuan
// Release year:2020.1

#pragma once
#include "CoreMinimal.h"
#if WITH_EDITOR
#include "GraphEditor/Public/SGraphPin.h"
#include "UnrealEd/Public/EdGraphUtilities.h"
#endif

#if WITH_EDITOR

class SEffectSlotNamePin :public SGraphPin
{
	SLATE_BEGIN_ARGS(SEffectSlotNamePin) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
	void OnMontageSelected(TSharedPtr<FString> ItemSlected, ESelectInfo::Type SelectInfo);
	virtual TSharedRef<SWidget>	GetDefaultValueWidget()override;

private:
	void SetEffectSlotNameList();


private:
	TArray<TSharedPtr<FString>>SEffectSlotNamePinList;
};

class FEffectSlotNameGraphPanelPinFactory :public FGraphPanelPinFactory
{
public:
	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;
};

#endif