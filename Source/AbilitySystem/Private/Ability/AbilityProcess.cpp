// Created by: ChengXinYuan
// Release year:2020.1

#include "Ability/AbilityProcess.h"

UAbilityProcess * UAbilityProcess::ActivateProcess(UProcessTask * ParentTask, TSubclassOf<UAbilityProcess> AbilityProcessClass, TMap<FName, FAttributeName> ProcessParam, FOnAbilityProcessComplete InOnAbilityProcessComplete)
{
	if (!ParentTask)
	{
		return nullptr;
	}

	if (UAbilityProcess* AbilityProcess = NewAbilityTask<UAbilityProcess>(ParentTask, ParentTask->GetCaster(), ParentTask->GetAbilityBlackBoard(), AbilityProcessClass))
	{
		AbilityProcess->OnAbilityProcessComplete = InOnAbilityProcessComplete;
		AbilityProcess->OnInit(ProcessParam);
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
	
	if (UAbilityProcess* AbilityProcess = NewAbilityTask<UAbilityProcess>(ParentTask, ParentTask->GetCaster(), ParentTask->GetAbilityBlackBoard(), AbilityProcessClass))
	{
		AbilityProcess->OnInit(ProcessParam);
		return AbilityProcess;
	}
	return nullptr;
}

void UAbilityProcess::FinishProcess(bool bSuccess, uint8 Result)
{
	OnProcessFinish(bSuccess);
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
	CompleteTask();
}

void UAbilityProcess::OnInit(TMap<FName, FAttributeName> AttributeNameList)
{
	FTaskParams TaskParams;
	TaskParams.Params = AttributeNameList;
	OnProcessActivate(TaskParams);
}
