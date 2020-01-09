// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/TaskBase.h"
#include "Ability/EffectTask.h"

void UTaskBase::Init(AActor* InCaster, UAbilityBlackBoard* InAbilityBlackBoard)
{
	Caster = InCaster;
	AbilityBlackBoard = InAbilityBlackBoard;
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
						EffectTask->InitEffectTask(Caster,AbilityBlackBoard,EffectInfo);
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

FAttributes UTaskBase::GetAttributes(FTaskParams TaskParams, FName ParamName)
{
	TMap<FName, FAttributes> InAttributesList;
	AttributeNameListConvertToAttributesList(TaskParams.Params, InAttributesList);
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
