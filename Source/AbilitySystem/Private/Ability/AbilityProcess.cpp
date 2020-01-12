// Created by: ChengXinYuan
// Release year:2020.1

#include "Ability/AbilityProcess.h"

UAbilityProcess * UAbilityProcess::ActivateProcess(UProcessTask * ParentTask, TSubclassOf<UAbilityProcess> AbilityProcessClass, TMap<FName, FAttributeName> ProcessParam, FOnAbilityProcessComplete InOnAbilityProcessComplete)
{
	if (!ParentTask)
	{
		return nullptr;
	}

	if (UAbilityProcess* AbilityProcess = NewAbilityTask<UAbilityProcess>(ParentTask, AbilityProcessClass))
	{
		AbilityProcess->OnAbilityProcessComplete = InOnAbilityProcessComplete;
		FTaskParams InTaskParams;
		AbilityProcess->Init(ParentTask->GetCaster(), ParentTask->GetAbilityBlackBoard(), InTaskParams);
		AbilityProcess->FinishInit();
		return AbilityProcess;
	}
	return nullptr;
}

UAbilityProcess* UAbilityProcess::ActivateProcess(UProcessTask* ParentTask, TSubclassOf<UAbilityProcess>AbilityProcessClass, TMap<FName, FAttributeName> ProcessParam)
{
	if (!ParentTask)
	{
		return nullptr;
	}
	
	if (UAbilityProcess* AbilityProcess = NewAbilityTask<UAbilityProcess>(ParentTask, AbilityProcessClass))
	{
		FTaskParams InTaskParams;
		InTaskParams.Params = ProcessParam;
		AbilityProcess->Init(ParentTask->GetCaster(), ParentTask->GetAbilityBlackBoard(), InTaskParams);
		AbilityProcess->FinishInit();
		return AbilityProcess;
	}
	return nullptr;
}

void UAbilityProcess::FinishProcess(bool bSuccess, uint8 Result)
{
	if (bSuccess)
	{
		OnAbilityProcessSuccess.Broadcast(Result);
	}
	else
	{
		OnAbilityProcessFail.Broadcast(Result);
	}
	OnAbilityProcessComplete.ExecuteIfBound(bSuccess);
	OnAbilityProcessComplete.Unbind();
	FinishTask();
}