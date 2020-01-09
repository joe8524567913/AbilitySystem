// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Ability/TaskBase.h"
#include "GameFramework/Actor.h"
#include "EffectTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ABILITYSYSTEM_API UEffectTask : public UTaskBase
{
	GENERATED_BODY()

public:
	void InitEffectTask(AActor* InCaster,UAbilityBlackBoard* InAbilityBlackBoard,FEffectInfo InEffectInfo);

protected:
	UFUNCTION(BlueprintCallable, Category = "EffectTask")
		void EndEffectTask();

	UFUNCTION(BlueprintImplementableEvent, Category = "EffectTask")
		void OnEffectActivate(FTaskParams TaskParams);

	UFUNCTION(BlueprintImplementableEvent, Category = "EffectTask")
		void OnTimePointActivate();

	UFUNCTION(BlueprintImplementableEvent, Category = "EffectTask")
		void OnEnd();

private:
	void LifeCountdown();
	void ActivateInterval();
	void ActivateTimePoints(int CurrentIndex);

	UFUNCTION()
		void OnTimePointsReached(int CurrentIndex);

	FEffectInfo EffectInfo;
	TArray<float> TimePoints;
	FTimerHandle IntervalHandle;
	FTimerHandle LifeHandle;
};
