// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "Ability/AbilityBlackBoard.h"
#include "GameFramework/Actor.h"
#include "TaskBase.generated.h"

/**
 * 
 */
class UEffectTask;

USTRUCT(Blueprintable)
struct FTaskParams
{
	GENERATED_USTRUCT_BODY()

	TMap<FName, FAttributeName> Params;
};

USTRUCT()
struct FEffectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		FEffectSlot EffectSlot;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TSubclassOf<UEffectTask> EffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		float Life;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		bool bTimePoints;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		float IntervalTime;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TArray<float> TimePoints;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TMap<FName, FAttributeName> AttributeNameList;

	bool IsValid() { return EffectClass; }

};

UCLASS()
class ABILITYSYSTEM_API UTaskBase : public UGameplayTask
{
	GENERATED_BODY()

public:
	static UTaskBase* NewTaskBase();
	virtual void Init(AActor* Caster, UAbilityBlackBoard* AbilityBlackBoard);
	virtual void CompleteTask() {};
	virtual UWorld* GetWorld() const override { return Caster ? Caster->GetWorld() : nullptr; }

	FORCEINLINE void AddToSubTaskMap(UTaskBase* Task) { SubTaskMap.Add(Task->GetFName(), Task); }
	FORCEINLINE void RemoveFromeSubTaskMap(UTaskBase* Task) { SubTaskMap.Remove(Task->GetFName()); }
	FORCEINLINE void SetParentTask(UTaskBase* InParentTask) { ParentTask = InParentTask; }
	FORCEINLINE UTaskBase* GetParentTask() { return ParentTask; }

	UFUNCTION(BlueprintCallable, Category = "Task")
		void ActivateEffectTask(FEffectSlot EffectSlot);

	UFUNCTION(BlueprintPure, Category = "Task")
		AActor* GetCaster() { return Caster; }

	UFUNCTION(BlueprintPure, Category = "Task")
		UAbilityBlackBoard* GetAbilityBlackBoard() { return AbilityBlackBoard; }


protected:
	TArray<FEffectInfo> FindEffectInfo(const FEffectSlot EffectSlot);

	UFUNCTION(BlueprintPure, Category = "Task")
		FAttributes GetAttributes(FTaskParams TaskParams, FName ParamName);


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TArray<FEffectInfo> EffectList;

	UTaskBase* ParentTask;
	TMap<FName, UTaskBase*> SubTaskMap;
	AActor* Caster;
	UAbilityBlackBoard* AbilityBlackBoard;


private:
	void AttributeNameListConvertToAttributesList(const TMap<FName, FAttributeName>& AttributeNameList, TMap<FName, FAttributes>& AttributesList);

};