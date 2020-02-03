// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability/AbilityBlackBoard.h"
#include "Ability/Ability.h"
#include "AbilityComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEnded);


UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
		virtual void RegisterAbility(TSubclassOf<UAbility>AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
		virtual void UnRegisterAbility(TSubclassOf<UAbility>AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
		virtual UAbility* ActivateAbility(TSubclassOf<UAbility>AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "AbilityComponent")
		virtual UAbility* RegisterAndActivateAbility(TSubclassOf<UAbility>AbilityClass);

	UFUNCTION(BlueprintPure, Category = "AbilityComponent")
		bool IsAbilityRegistered(TSubclassOf<UAbility>AbilityClass) { return AbilityMap.Contains(AbilityClass->GetFullName()); }

public:
	UPROPERTY(BlueprintAssignable, Category = "AbilityBlackBoard")
		FOnAbilityEnded OnCurrentAbilityEnd;

protected:
	virtual UAbilityBlackBoard* RegisterAbilityBlackBoard();

protected:
	UFUNCTION()
		void OnCurrentAbilityComplete();

	TMap<FString,UAbility*> AbilityMap;

private:
	FORCEINLINE virtual UAbilityBlackBoard* CreateAbilityBlackBoardTemplate();
	FORCEINLINE UAbility* FindAbilityByClass(TSubclassOf<UAbility>AbilityClass) { return *AbilityMap.Find(AbilityClass->GetFullName()); }
	UAbility* CurrentAbility;

		
};
