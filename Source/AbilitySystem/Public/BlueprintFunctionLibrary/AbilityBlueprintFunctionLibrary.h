// Created by: ChengXinYuan
// Release year:2020.1

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Ability/AbilityBlackBoard.h"
#include "AbilityBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UAbilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (CommutativeAssociativeBinaryOperator = "true"), Category = "AbilityBlueprintFunctionLibrary")
		static int32 MakeContentParam(FAttributeName A, FAttributeName B);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetBoolAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UBoolProperty*Value);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetIntAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UIntProperty*Value);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetEnumAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UByteProperty*Value);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetFloatAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UFloatProperty*Value);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetNameAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UNameProperty*Value);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetStringAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UStrProperty*Value);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetObjectAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UObjectProperty*Value);

	UFUNCTION(BlueprintCallable, Category = "AbilityBlackBoard", CustomThunk, meta = (CustomStructureParam = "Value"))
		static void SetClassAttribute(UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName, UClassProperty*Value);

	UFUNCTION(BlueprintPure,meta = (BlueprintAutocast), Category = "AbilityBlueprintFunctionLibrary")
		static bool AttributesConvertToBool(FAttributes Attribute,bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast), Category = "AbilityBlueprintFunctionLibrary")
		static int32 AttributesConvertToInt(FAttributes Attribute, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast), Category = "AbilityBlueprintFunctionLibrary")
		static float AttributesConvertToFloat(FAttributes Attribute, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast), Category = "AbilityBlueprintFunctionLibrary")
		static FName AttributesConvertToName(FAttributes Attribute, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast), Category = "AbilityBlueprintFunctionLibrary")
		static FString AttributesConvertToString(FAttributes Attribute, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast), Category = "AbilityBlueprintFunctionLibrary")
		static UObject* AttributesConvertToObject(FAttributes Attribute, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast), Category = "AbilityBlueprintFunctionLibrary")
		static UClass* AttributesConvertToUClass(FAttributes Attribute, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "=="), Category = "AbilityBlueprintFunctionLibrary")
		static bool IsAttributeNameEqual(FAttributeName A, FAttributeName B) { return A == B; }

	template<typename ValueType>static void SetAttributes(FFrame& Stack,UAbilityBlackBoard*AbilityBlackBoard, FAttributeName AttributeName);

	template<typename ValueType, typename PropertyType>static ValueType ACastTo(FAttributes AttributeProperty, bool& bSuccess);

public:
	DECLARE_FUNCTION(execSetBoolAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UBoolProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}

	DECLARE_FUNCTION(execSetIntAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UIntProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}

	DECLARE_FUNCTION(execSetEnumAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UByteProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}

	DECLARE_FUNCTION(execSetFloatAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UFloatProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}

	DECLARE_FUNCTION(execSetNameAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UNameProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}

	DECLARE_FUNCTION(execSetStringAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UStrProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}

	DECLARE_FUNCTION(execSetObjectAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UObjectProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}

	DECLARE_FUNCTION(execSetClassAttribute)
	{
		P_GET_OBJECT(UAbilityBlackBoard, AbilityBlackBoard);
		P_GET_STRUCT(FAttributeName, AttributeName);
		SetAttributes<UClassProperty>(Stack, AbilityBlackBoard, AttributeName);
		P_FINISH;
	}
	
};

template<typename ValueType>
inline void UAbilityBlueprintFunctionLibrary::SetAttributes(FFrame & Stack, UAbilityBlackBoard * AbilityBlackBoard, FAttributeName AttributeName)
{
	Stack.Step(Stack.Object, NULL);
	if (Stack.MostRecentProperty)
	{
		ValueType * Property = ExactCast <ValueType>(Stack.MostRecentProperty);
		void * PropertyAddress = Stack.MostRecentPropertyAddress;

		ensureMsgf(Property, TEXT("Value is the wrong type"));

		AbilityBlackBoard->AddAttributesByProperty(AttributeName, Property, PropertyAddress);
	}
}

template<typename ValueType, typename PropertyType>
inline ValueType UAbilityBlueprintFunctionLibrary::ACastTo(FAttributes Attribute, bool& bSuccess)
{
	PropertyType* Property = Cast<PropertyType>(Attribute.AttributeProperty);
	bSuccess = Property;

	return Property->GetPropertyValue(Attribute.AttributeAddress);
}
