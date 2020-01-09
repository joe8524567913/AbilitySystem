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
class ABILITYSYSTEM_API UProcessTask : public UTaskBase
{
	GENERATED_BODY()

public:
	virtual void CompleteTask() override;
	virtual void Interrupt();
	virtual void OnInterrupt();
	void EndSubTasks();

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInterrupt"), Category = "Ability")
		void K2_OnInterrupt();
};

template<typename TaskType>
FORCEINLINE TaskType * NewAbilityTask(UObject* Outer,AActor* Caster, UAbilityBlackBoard* AbilityBlackBoard,UClass* Class,FName Name = NAME_None)
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
	NewAbilityTask->Init(Caster, AbilityBlackBoard);
	return NewAbilityTask;
}
