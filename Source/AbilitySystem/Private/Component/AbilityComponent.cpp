// Created by: ChengXinYuan
// Release year:2020.1


#include "Component/AbilityComponent.h"
#include "Settings/AbilitySettings.h"
#include "..\..\Public\Component\AbilityComponent.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilityComponent::RegisterAbility(TSubclassOf<UAbility> AbilityClass)
{
	if (!AbilityClass)
	{
		return;
	}
	AbilityMap.Add(AbilityClass->GetFullName(), NewAbilityTask<UAbility>(this, GetOwner(), RegisterAbilityBlackBoard(), AbilityClass));
}

void UAbilityComponent::UnRegisterAbility(TSubclassOf<UAbility> AbilityClass)
{
	if (!AbilityClass)
	{
		return;
	}
	if (IsAbilityRegistered(AbilityClass))
	{
		AbilityMap.Remove(AbilityClass->GetFullName());
	}
}

UAbility * UAbilityComponent::ActivateAbility(TSubclassOf<UAbility> AbilityClass)
{
	if (!AbilityClass)
	{
		return nullptr;
	}
	if (CurrentAbility&&!CurrentAbility->IsPendingKill())
	{
		if (CurrentAbility->IsActivate())
		{
			CurrentAbility->Interrupt();
		}
	}
	CurrentAbility = FindAbilityByClass(AbilityClass);
	if (CurrentAbility)
	{
		CurrentAbility->OnAbilityComplete.Clear();
		CurrentAbility->OnAbilityComplete.AddDynamic(this, &UAbilityComponent::OnCurrentAbilityComplete);
		CurrentAbility->OnAbilityActivate();
		return CurrentAbility;
	}
	return nullptr;
}

UAbility * UAbilityComponent::RegisterAndActivateAbility(TSubclassOf<UAbility> AbilityClass)
{
	if (!AbilityClass)
	{
		return nullptr;
	}
	if (IsAbilityRegistered(AbilityClass))
	{
		if (UAbility* InAbility = ActivateAbility(AbilityClass))
		{
			return InAbility;
		}
		else
		{
			RegisterAbility(AbilityClass);
			return ActivateAbility(AbilityClass);
		}
	}
	else
	{
		RegisterAbility(AbilityClass);
		return ActivateAbility(AbilityClass);
	}
}

UAbilityBlackBoard* UAbilityComponent::RegisterAbilityBlackBoard()
{
	return CreateAbilityBlackBoardTemplate();
}

void UAbilityComponent::OnCurrentAbilityComplete()
{
	OnCurrentAbilityEnd.Broadcast();
	CurrentAbility->OnAbilityComplete.Clear();
	CurrentAbility = nullptr;
}

UAbilityBlackBoard * UAbilityComponent::CreateAbilityBlackBoardTemplate()
{
	TSubclassOf<UAbilityBlackBoard> InAbilityBlackBoardTemplate = GetMutableDefault<UAbilitySettings>()->AbilityBlackBoardTemplate;
	return InAbilityBlackBoardTemplate ? NewObject<UAbilityBlackBoard>(this, InAbilityBlackBoardTemplate, TEXT("")) : nullptr;
}

