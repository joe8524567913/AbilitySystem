// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySettings.generated.h"

/**
 * 
 */
class UAbilityBlackBoard;

UCLASS(config = Game, defaultconfig)
class UAbilitySettings : public UObject
{
	GENERATED_BODY()

	UAbilitySettings(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(config, EditDefaultsOnly, Category = "Ability")
		TSubclassOf<UAbilityBlackBoard> AbilityBlackBoardTemplate;
	
};
