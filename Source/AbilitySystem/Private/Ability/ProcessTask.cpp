// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/ProcessTask.h"

void UProcessTask::OnEnded()
{
	EndSubTasks();
}

void UProcessTask::Interrupt()
{
	OnInterrupt();
	FinishTask();
}

void UProcessTask::OnInterrupt()
{
	K2_OnInterrupt();
}

void UProcessTask::EndSubTasks()
{
	for (TMap<FName, UTaskBase*>::TConstIterator Iter = SubTaskMap.CreateConstIterator(); Iter; ++Iter)
	{
		if (UTaskBase* TaskBase = Iter->Value)
		{
			TaskBase->FinishTask();
		}
	}
	SubTaskMap.Empty();
	if (ParentTask)
	{
		ParentTask = nullptr;
	}
}
