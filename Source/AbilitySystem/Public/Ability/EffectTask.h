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
class UEffectTask : public UTaskBase
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetEffectInfo(FEffectInfo InEffectInfo) { EffectInfo = InEffectInfo; }

protected:
	virtual void OnActivate() override;
	virtual void OnEnded() override;

	UFUNCTION(BlueprintCallable, Category = "EffectTask")
		void EndEffectTask();

	UFUNCTION(BlueprintImplementableEvent, Category = "EffectTask")
		void OnTimePointActivate();

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
