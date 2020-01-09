// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
// Created by: ChengXinYuan
// Release year:2020.1

#include "AbilitySystem.h"
#if WITH_EDITOR
#include "PropertyEditor/Public/PropertyEditorModule.h"
#include "Settings/Public/ISettingsModule.h"
#include "Settings/Public/ISettingsContainer.h"
#include "Settings/Public/ISettingsSection.h"
#endif
#include "Modules/ModuleManager.h"
#include "Settings/AbilitySettings.h"



#define LOCTEXT_NAMESPACE "FAbilitySystemModule"

void FAbilitySystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if WITH_EDITOR

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("AttributeName"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FAttributeNameDetailsViewCustomizations::MakeInstance));
	PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("EffectSlot"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FEffectSlotNameDetailsViewCustomizations::MakeInstance));
	
	AtributePanelGraphPinFactory = MakeShareable(new FAtributeNameGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(AtributePanelGraphPinFactory);

	EffectSlotNamePanelGraphPinFactory = MakeShareable(new FEffectSlotNameGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(EffectSlotNamePanelGraphPinFactory);

	RegisterSettings();

#endif

}

void FAbilitySystemModule::ShutdownModule()
{
#if WITH_EDITOR

	if (UObjectInitialized())
	{
		UnregisterSettings();
	}

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("AttributeName"));
	PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("EffectSlot"));

	FEdGraphUtilities::UnregisterVisualPinFactory(AtributePanelGraphPinFactory);
	FEdGraphUtilities::UnregisterVisualPinFactory(EffectSlotNamePanelGraphPinFactory);

#endif
}

bool FAbilitySystemModule::SupportsDynamicReloading()
{
	return true;
}

void FAbilitySystemModule::RegisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("Ability",
			LOCTEXT("RuntimeWDCategoryName", "Ability"),
			LOCTEXT("RuntimeWDCategoryDescription", "Ability settings"));

		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Ability", "AbilityTemplate",
			LOCTEXT("RuntimeGeneralSettingsName", "AbilityTemplate"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "AbilityTemplate"),
			GetMutableDefault<UAbilitySettings>()
		);
		
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FAbilitySystemModule::HandleSettingsSaved);
		}
		
	}
#endif
}

void FAbilitySystemModule::UnregisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Ability", "AbilityTemplate");
	}
#endif
}

bool FAbilitySystemModule::HandleSettingsSaved()
{
	UAbilitySettings* Settings = GetMutableDefault<UAbilitySettings>();
	Settings->SaveConfig();
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAbilitySystemModule, AbilitySystem)