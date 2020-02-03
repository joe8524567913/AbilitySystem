// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Ability/TaskBase.h"
#include "Ability/AbilityBlackBoard.h"
#include "ProcessTask.generated.h"

/**
 * 
 */
UCLASS()
class UProcessTask : public UTaskBase
{
	GENERATED_BODY()

protected:
	virtual void OnEnded() override;
	virtual void OnInterrupt()override;

private:
	void EndSubTasks(bool bInterrupt = false);

};

template<typename TaskType>
FORCEINLINE TaskType * NewAbilityTask(UObject* Outer,UClass* Class,FName Name = NAME_None)
{
	TaskType* NewAbilityTask = NewObject<TaskType>(Outer, Class, Name);
	if (!NewAbilityTask)
	{
		return nullptr;
	}
	if (UProcessTask* ParentTask = Cast<UProcessTask>(Outer))
	{
		ParentTask->AddToSubTaskMap(NewAbilityTask);
		NewAbilityTask->SetParentTask(ParentTask);
	}
	return NewAbilityTask;
}
