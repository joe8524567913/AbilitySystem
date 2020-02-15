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

UENUM()
namespace EEffectTaskActivateType
{
	enum Type
	{
		ETCT_None UMETA(DisplayName = "None"),
		ETCT_IntervalTime UMETA(DisplayName = "IntervalTime"),
		ETCT_TimePoint UMETA(DisplayName = "TimePoint"),
	};
}

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
		TEnumAsByte<EEffectTaskActivateType::Type>ActivateType;

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
	void Init(AActor* Caster, UAbilityBlackBoard* AbilityBlackBoard, FTaskParams InTaskParams);
	void FinishInit();
	void FinishTask(bool bInterrupt = false, bool bKill = false);
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
	virtual void OnActivate() {};
	virtual void OnEnded() {}
	virtual void OnInterrupt() {};

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPreActivate"), Category = "TaskBase")
		void K2_OnPreActivate(FTaskParams InTaskParams);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnActivate"), Category = "TaskBase")
		void K2_OnActivate();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnEnded"), Category = "TaskBase")
		void K2_OnEnded();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInterrupt"), Category = "TaskBase")
		void K2_OnInterrupt();

	UFUNCTION(BlueprintPure, Category = "Task")
		FAttributes GetAttributes(FTaskParams InTaskParams, FName ParamName, bool& bSuccess);

	TArray<FEffectInfo> FindEffectInfo(const FEffectSlot EffectSlot);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TArray<FEffectInfo> EffectList;

	UPROPERTY()
		AActor* Caster;

	UTaskBase* ParentTask;
	FTaskParams TaskParams;
	TMap<FName, UTaskBase*> SubTaskMap;
	UAbilityBlackBoard* AbilityBlackBoard;



private:
	void AttributeNameListConvertToAttributesList(const TMap<FName, FAttributeName>& AttributeNameList, TMap<FName, FAttributes>& AttributesList);

};
