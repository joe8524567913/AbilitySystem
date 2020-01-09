// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Ability/ProcessTask.h"
#include "Ability.generated.h"

/**
 * 
 */
class UAbilityProcess;

USTRUCT(Blueprintable)
struct FProcessSequenceInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProcessSequence")
		TSubclassOf<UAbilityProcess> AbilityProcessClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProcessSequence")
		TMap<FName, FAttributeName> AttributesList;

	FORCEINLINE bool IsValid() { return AbilityProcessClass ? true : false; }
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAbilityProcessComplete, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityComplete);

UCLASS(Blueprintable)
class ABILITYSYSTEM_API UAbility : public UProcessTask
{
	GENERATED_BODY()

public:
	virtual void OnAbilityActivate();
	virtual void OnAbilityEnd();
	virtual void OnInterrupt() override;
	virtual void Interrupt() override;
	FORCEINLINE bool IsActivate() { return bActivate; }

	FOnAbilityComplete OnAbilityComplete;

protected:
	virtual UAbilityProcess* ActivateProcess();
	virtual void ActivateAbilityProcessSequence();

	UFUNCTION()
		void OnAbilityProcessComplete(bool bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void EndAbility();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ActivateAbilityProcessSequence"), Category = "Ability")
		void K2_ActivateAbilityProcessSequence();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAbilityActivate"), Category = "Ability")
		void K2_OnAbilityActivate();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnAbilityEnd"), Category = "Ability")
		void K2_OnAbilityEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Process")
		bool bAutoActivateAbilitySequence = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Process")
		TArray<FProcessSequenceInfo>ProcessSequence;


private:
	FORCEINLINE FProcessSequenceInfo GetNextProcessSequenceInfo();
	void ResetAbiity();
	void ClearCurrentProcess();

	bool bActivate = false;
	bool bContinue = true;
	int32 CurrentProcessIndex = 0;
	UAbilityProcess* CurrentProcess;
	FOnAbilityProcessComplete OnAbilityProcessCompleteDelegate;

	
};
