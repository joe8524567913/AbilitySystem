// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "DetailCustomizations/AttributeNamePin.h"
#include "DetailCustomizations/EffectSlotNamePin.h"
#include "DetailCustomizations/AttributeNameDetailsViewCustomizations.h"
#include "DetailCustomizations/EffectSlotNameDetailsViewCustomizations.h"
#include "DetailCustomizations/EffectInfoDetailsViewCustomizations.h"

class FAbilitySystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override;

private:
	void RegisterSettings();
	void UnregisterSettings();
	bool HandleSettingsSaved();

#if WITH_EDITOR
	TSharedPtr<FAtributeNameGraphPanelPinFactory> AtributePanelGraphPinFactory;
	TSharedPtr<FEffectSlotNameGraphPanelPinFactory> EffectSlotNamePanelGraphPinFactory;
#endif


};
