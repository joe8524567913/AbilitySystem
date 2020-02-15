// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/Ability.h"
#include "Ability/AbilityProcess.h"

void UAbility::OnActivate()
{
	bActivate = true;
	if (bAutoActivateAbilitySequence)
	{
		ActivateAbilityProcessSequence();
	}
}

void UAbility::OnEnded()
{
	Super::OnEnded();
	ClearCurrentProcess(false);
	OnAbilityComplete.Broadcast();
	ResetAbiity();
}

void UAbility::OnInterrupt()
{
	Super::OnInterrupt();
	ClearCurrentProcess(true);
	ResetAbiity();
}

void UAbility::EndAbility()
{
	FinishTask(false, false);
}

void UAbility::K2_ActivateAbilityProcessSequence()
{
	ActivateAbilityProcessSequence();
}

UAbilityProcess* UAbility::ActivateProcess()
{
	FProcessSequenceInfo ProcessSequenceInfo = GetNextProcessSequenceInfo();
	if (ProcessSequenceInfo.IsValid())
	{
		CurrentProcessIndex++;
		OnAbilityProcessCompleteDelegate.BindUFunction(this, TEXT("OnAbilityProcessComplete"));
		UAbilityProcess* InProcess = UAbilityProcess::ActivateProcess(this, ProcessSequenceInfo.AbilityProcessClass, ProcessSequenceInfo.AttributesList, OnAbilityProcessCompleteDelegate);
		if (!InProcess || InProcess->IsPendingKill())
		{
			return nullptr;
		}

		return InProcess;
	}
	else
	{
		return nullptr;
	}
}

void UAbility::ActivateAbilityProcessSequence()
{
	CurrentProcess = ActivateProcess();
	if (!CurrentProcess)
	{
		EndAbility();
	}
}

void UAbility::OnAbilityProcessComplete(bool bSuccess)
{
	ClearCurrentProcess(false);
	if (bSuccess)
	{
		ActivateAbilityProcessSequence();
	}
	else
	{
		EndAbility();
	}
}

FProcessSequenceInfo UAbility::GetNextProcessSequenceInfo()
{
	return ProcessSequence.Num() > CurrentProcessIndex ? ProcessSequence[CurrentProcessIndex] : FProcessSequenceInfo();
}

void UAbility::ResetAbiity()
{
	bActivate = false;
	CurrentProcessIndex = 0;
}

void UAbility::ClearCurrentProcess(bool bInterrupt)
{
	if (CurrentProcess)
	{
		CurrentProcess->FinishTask(bInterrupt, true);
		CurrentProcess = nullptr;
	}
	OnAbilityProcessCompleteDelegate.Unbind();
}
