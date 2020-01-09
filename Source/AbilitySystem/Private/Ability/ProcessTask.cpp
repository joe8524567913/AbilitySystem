// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/ProcessTask.h"

void UProcessTask::CompleteTask()
{
	EndSubTasks();
	EndTask();
}

void UProcessTask::Interrupt()
{
	OnInterrupt();
	CompleteTask();
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
			TaskBase->CompleteTask();
		}
	}
	SubTaskMap.Empty();
	if (ParentTask)
	{
		ParentTask = nullptr;
	}
}
