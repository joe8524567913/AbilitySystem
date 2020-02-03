// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Ability/ProcessTask.h"
#include "Ability/Ability.h"
#include "Component/AbilityComponent.h"
#include "AbilityProcess.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityProcessDelegate, uint8, Result);

UCLASS(Blueprintable)
class UAbilityProcess : public UProcessTask
{
	GENERATED_BODY()

public:
	static UAbilityProcess* ActivateProcess(UProcessTask* ParentTask, TSubclassOf<UAbilityProcess>AbilityProcessClass, TMap<FName, FAttributeName> ProcessParam, FOnAbilityProcessComplete InOnAbilityProcessComplete);

	UFUNCTION(BlueprintCallable, Category = "AbilityProcess",meta = (BlueprintInternalUseOnly = "TRUE"))
		static UAbilityProcess* ActivateProcess(UProcessTask* ParentTask,TSubclassOf<UAbilityProcess>AbilityProcessClass, TMap<FName, FAttributeName> ProcessParam);

	UFUNCTION(BlueprintCallable,meta = (AdvancedDisplay = "Result"), Category = "AbilityProcess")
		virtual void FinishProcess(bool bSuccess, uint8 Result = 0);

	UPROPERTY(BlueprintAssignable)
		FAbilityProcessDelegate OnAbilityProcessSuccess;

	UPROPERTY(BlueprintAssignable)
		FAbilityProcessDelegate OnAbilityProcessFail;

	FOnAbilityProcessComplete OnAbilityProcessComplete;
};
