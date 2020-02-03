// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/ProcessTask.h"

void UProcessTask::OnEnded()
{
	EndSubTasks(false);
}

void UProcessTask::OnInterrupt()
{
	EndSubTasks(true);
}

void UProcessTask::EndSubTasks(bool bInterrupt)
{
	for (TMap<FName, UTaskBase*>::TConstIterator Iter = SubTaskMap.CreateConstIterator(); Iter; ++Iter)
	{
		if (UTaskBase* TaskBase = Iter->Value)
		{
			TaskBase->FinishTask(bInterrupt,true);
		}
	}
	SubTaskMap.Empty();
	if (ParentTask)
	{
		ParentTask = nullptr;
	}
}
