// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/TaskBase.h"
#include "Ability/EffectTask.h"

void UTaskBase::Init(AActor* InCaster, UAbilityBlackBoard* InAbilityBlackBoard, FTaskParams InTaskParams)
{
	Caster = InCaster;
	AbilityBlackBoard = InAbilityBlackBoard;
	TaskParams = InTaskParams;
}

void UTaskBase::FinishInit()
{
	OnActivate();
	K2_OnActivate(TaskParams);
}

void UTaskBase::FinishTask(bool bInterrupt, bool bKill)
{
	if (bInterrupt)
	{
		K2_OnInterrupt();
		OnInterrupt();
	}
	else
	{
		K2_OnEnded();
		OnEnded();
	}
	if (bKill)
	{
		EndTask();
	}
}

void UTaskBase::ActivateEffectTask(FEffectSlot EffectSlot)
{
	UTaskBase * Task = this;
	while (Task&&!Task->IsPendingKill())
	{
		TArray<FEffectInfo>EffectInfoList = Task->FindEffectInfo(EffectSlot);
		if (EffectInfoList.Num())
		{
			for (FEffectInfo EffectInfo:EffectInfoList)
			{
				if (EffectInfo.IsValid())
				{
					if (UEffectTask* EffectTask = NewObject<UEffectTask>(GetCaster(), EffectInfo.EffectClass))
					{
						FTaskParams InTaskParams;
						InTaskParams.Params = EffectInfo.AttributeNameList;
						EffectTask->Init(Caster, AbilityBlackBoard, InTaskParams);
						EffectTask->SetEffectInfo(EffectInfo);
						EffectTask->FinishInit();
					}
				}
				
			}
		}
		Task = Task->GetParentTask();
	}
}

TArray<FEffectInfo> UTaskBase::FindEffectInfo(const FEffectSlot EffectSlot)
{
	TArray<FEffectInfo>EffectInfoList;
	for (FEffectInfo InEffectInfo:EffectList)
	{
		if (InEffectInfo.EffectSlot == EffectSlot)
		{
			EffectInfoList.Add(InEffectInfo);
		}
	}
	return EffectInfoList;
}

FAttributes UTaskBase::GetAttributes(FTaskParams InTaskParams, FName ParamName)
{
	TMap<FName, FAttributes> InAttributesList;
	AttributeNameListConvertToAttributesList(InTaskParams.Params, InAttributesList);
	return *InAttributesList.Find(ParamName);
}

void UTaskBase::AttributeNameListConvertToAttributesList(const TMap<FName, FAttributeName>& AttributeNameList, TMap<FName, FAttributes>& AttributesList)
{
	if (!AbilityBlackBoard)
	{
		return;
	}

	for (TPair<FName, FAttributeName> AttributePair : AttributeNameList)
	{
		AttributesList.Add(AttributePair.Key, AbilityBlackBoard->FindAttribute(AttributePair.Value));
	}
}
