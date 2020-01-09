// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/EffectTask.h"
#include "TimerManager.h"
#include "Engine/World.h"

void UEffectTask::InitEffectTask(AActor* InCaster, UAbilityBlackBoard* InAbilityBlackBoard, FEffectInfo InEffectInfo)
{
	Init(InCaster, InAbilityBlackBoard);
	EffectInfo = InEffectInfo;

	FTaskParams TaskParams;
	TaskParams.Params = EffectInfo.AttributeNameList;
	OnEffectActivate(TaskParams);

	LifeCountdown();
	if (EffectInfo.bTimePoints)
	{
		TimePoints = EffectInfo.TimePoints;
		ActivateTimePoints(0);
	}
	else
	{
		ActivateInterval();
	}
}

void UEffectTask::EndEffectTask()
{
	if (UWorld* InWorld = Caster->GetWorld())
	{
		InWorld->GetTimerManager().ClearTimer(IntervalHandle);
		InWorld->GetTimerManager().ClearTimer(LifeHandle);
	}

	OnEnd();
	EndTask();
}

void UEffectTask::LifeCountdown()
{
	if (Caster)
	{
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UEffectTask::EndEffectTask);
		Caster->GetWorld()->GetTimerManager().SetTimer(LifeHandle, TimerDelegate, EffectInfo.Life, false);
	}
}

void UEffectTask::ActivateInterval()
{
	if (Caster)
	{
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UEffectTask::OnTimePointActivate);
		Caster->GetWorld()->GetTimerManager().SetTimer(IntervalHandle, TimerDelegate, EffectInfo.IntervalTime, true, -1.f);
	}
}

void UEffectTask::ActivateTimePoints(int CurrentIndex)
{
	if (CurrentIndex< TimePoints.Num())
	{
		int LastIndex = CurrentIndex - 1;
		float DelayTime = LastIndex >= 0 ? TimePoints[CurrentIndex] - TimePoints[LastIndex] : TimePoints[CurrentIndex];

		if (Caster)
		{
			FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UEffectTask::OnTimePointsReached, CurrentIndex);
			Caster->GetWorld()->GetTimerManager().SetTimer(IntervalHandle, TimerDelegate, DelayTime, false, -1.f);
		}
	}
	else
	{
		OnEnd();
	}
}

void UEffectTask::OnTimePointsReached(int CurrentIndex)
{
	OnTimePointActivate();
	ActivateTimePoints(CurrentIndex + 1);
}
