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

	FORCEINLINE bool IsValid() { return AbilityProcessClass; }
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAbilityProcessComplete, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityComplete);

UCLASS(Blueprintable)
class ABILITYSYSTEM_API UAbility : public UProcessTask
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsActivate() { return bActivate; }

	FOnAbilityComplete OnAbilityComplete;

protected:
	virtual void OnActivate() override;
	virtual void OnEnded() override;
	virtual void OnInterrupt() override;

	virtual UAbilityProcess* ActivateProcess();
	virtual void ActivateAbilityProcessSequence();

	FORCEINLINE bool IsActivating() { return bActivate; }

	UFUNCTION()
		void OnAbilityProcessComplete(bool bSuccess);

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void EndAbility();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ActivateAbilityProcessSequence"), Category = "Ability")
		void K2_ActivateAbilityProcessSequence();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Process")
		bool bAutoActivateAbilitySequence = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Process")
		TArray<FProcessSequenceInfo>ProcessSequence;


private:
	FORCEINLINE FProcessSequenceInfo GetNextProcessSequenceInfo();
	void ResetAbiity();
	void ClearCurrentProcess(bool bInterrupt = false);

	bool bActivate = false;
	int32 CurrentProcessIndex = 0;
	UAbilityProcess* CurrentProcess;
	FOnAbilityProcessComplete OnAbilityProcessCompleteDelegate;

	
};
