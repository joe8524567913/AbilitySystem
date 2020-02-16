// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityBlackBoard.generated.h"

/**
 * 
 */

class UAnimMontage;

USTRUCT(BlueprintType)
struct FAttributeName
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "AbilityBlackBoard")
		FName Attribute;

	bool operator == (const FAttributeName&AttributeName)
	{
		return Attribute == AttributeName.Attribute;
	}
};

USTRUCT(BlueprintType)
struct FAttributes
{
	GENERATED_USTRUCT_BODY()

	UProperty* AttributeProperty;
	
	void*AttributeAddress;

};

USTRUCT(BlueprintType)
struct FEffectSlot
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityBlackBoard")
		FName SlotName;

	bool operator == (const FEffectSlot&EffectSlot)
	{
		return SlotName == EffectSlot.SlotName;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChange, FAttributeName, AttributeName, FAttributes, LastAttribute, FAttributes, NewAttribute);

UCLASS(Blueprintable)
class ABILITYSYSTEM_API UAbilityBlackBoard : public UDataAsset
{
	GENERATED_BODY()
		
public:	
	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		int32 GetAttributeAsInt32(FAttributeName AttributeName, bool& bSuccess);

	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		float GetAttributeAsFloat(FAttributeName AttributeName, bool& bSuccess);
	/*
	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		FVector GetAttributeAsVector(FAttributeName AttributeName, bool& bSuccess);
	*/
	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		bool GetAttributeAsBool(FAttributeName AttributeName, bool& bSuccess);

	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		uint8 GetAttributeAsEnum(FAttributeName AttributeName, bool& bSuccess);

	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		FName GetAttributeAsName(FAttributeName AttributeName, bool& bSuccess);

	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		FString GetAttributeAsString(FAttributeName AttributeName, bool& bSuccess);

	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		UObject* GetAttributeAsObject(FAttributeName AttributeName, bool& bSuccess);

	UFUNCTION(BlueprintPure, Category = "AbilityBlackBoard")
		UClass* GetAttributeAsClass(FAttributeName AttributeName, bool& bSuccess);


public:
	FORCEINLINE TMap<FName, FAttributes> GetAttributesList() { return AttributesList; }
	FORCEINLINE TArray<FName> GetEffectSlotList() { return EffectSlotList; }
	FORCEINLINE FAttributes FindAttribute(FAttributeName AttributeName) { return *AttributesList.Find(AttributeName.Attribute); }
	FORCEINLINE void AddAttributes(FAttributeName AttributeName, FAttributes Attributes) { AttributesList.Add(AttributeName.Attribute, Attributes); }
	FORCEINLINE void AddAttributesByProperty(FAttributeName AttributeName, UProperty* Property, void * PropertyAddress,bool bCallBack = false);
	template<typename ValueType, typename PropertyType>ValueType GetAttribute(FAttributeName AttributeName, bool& bSuccess);
	template<typename ValueType>ValueType GetStructAttribute(FAttributeName AttributeName, bool& bSuccess);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AbilityBlackBoard")
		TMap<FName, FAttributes>AttributesList;

	UPROPERTY(EditDefaultsOnly, Category = "AbilityBlackBoard")
		TArray<FName>EffectSlotList;


public:
	UPROPERTY(BlueprintAssignable, Category = "AbilityBlackBoard")
		FOnAttributeChange OnAttributeChange;
	
};

template<typename ValueType,typename PropertyType>
inline ValueType UAbilityBlackBoard::GetAttribute(FAttributeName AttributeName,bool& bSuccess)
{
	FAttributes Attributes = *AttributesList.Find(AttributeName.Attribute);
	return UAbilityBlueprintFunctionLibrary::ACastTo<ValueType, PropertyType>(Attributes, bSuccess);	 
}

template<typename ValueType>
inline ValueType UAbilityBlackBoard::GetStructAttribute(FAttributeName AttributeName, bool& bSuccess)
{
	FAttributes Attributes = *AttributesList.Find(AttributeName.Attribute);
	return UAbilityBlueprintFunctionLibrary::ACastToStruct<ValueType>(Attributes, bSuccess);
}
