// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/Ability.h"
#include "Ability/AbilityProcess.h"

void UAbility::OnAbilityActivate()
{
	bActivate = true;
	K2_OnAbilityActivate();
	if (bAutoActivateAbilitySequence)
	{
		ActivateAbilityProcessSequence();
	}
}

void UAbility::OnAbilityEnd()
{
	ResetAbiity();
	ClearCurrentProcess();
	OnAbilityComplete.Broadcast();
	K2_OnAbilityEnd();
}

void UAbility::OnInterrupt()
{
	ResetAbiity();
	ClearCurrentProcess();
	K2_OnInterrupt();
}

void UAbility::Interrupt()
{
	OnInterrupt();
	EndSubTasks();
}

void UAbility::EndAbility()
{
	GetCaster();
	OnAbilityEnd();
	EndSubTasks();
}

void UAbility::K2_ActivateAbilityProcessSequence()
{
	ActivateAbilityProcessSequence();
}

UAbilityProcess* UAbility::ActivateProcess()
{
	if (!bContinue)
	{
		return nullptr;
	}
	FProcessSequenceInfo ProcessSequenceInfo = GetNextProcessSequenceInfo();
	if (ProcessSequenceInfo.IsValid())
	{
		CurrentProcessIndex++;
		OnAbilityProcessCompleteDelegate.BindUFunction(this, TEXT("OnAbilityProcessComplete"));
		UAbilityProcess* InProcess = UAbilityProcess::ActivateProcess(this, ProcessSequenceInfo.AbilityProcessClass, ProcessSequenceInfo.AttributesList, OnAbilityProcessCompleteDelegate);
		if (!InProcess||InProcess->IsPendingKill())
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
	ClearCurrentProcess();
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
	bContinue = true;
	CurrentProcessIndex = 0;
}

void UAbility::ClearCurrentProcess()
{
	CurrentProcess = nullptr;
	OnAbilityProcessCompleteDelegate.Unbind();
}
