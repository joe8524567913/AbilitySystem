// Created by: ChengXinYuan
// Release year:2020.1

#include "BlueprintFunctionLibrary/AbilityBlueprintFunctionLibrary.h"

int32 UAbilityBlueprintFunctionLibrary::MakeContentParam(FAttributeName A, FAttributeName B)
{
	return 0;
}

bool UAbilityBlueprintFunctionLibrary::AttributesConvertToBool(FAttributes Attribute, bool& bSuccess)
{
	return ACastTo<bool, UBoolProperty>(Attribute, bSuccess);
}

int32 UAbilityBlueprintFunctionLibrary::AttributesConvertToInt(FAttributes Attribute, bool & bSuccess)
{
	return ACastTo<int32, UIntProperty>(Attribute, bSuccess);
}

float UAbilityBlueprintFunctionLibrary::AttributesConvertToFloat(FAttributes Attribute, bool & bSuccess)
{
	return ACastTo<float, UFloatProperty>(Attribute, bSuccess);
}

FName UAbilityBlueprintFunctionLibrary::AttributesConvertToName(FAttributes Attribute, bool & bSuccess)
{
	return ACastTo<FName, UNameProperty>(Attribute, bSuccess);
}

FString UAbilityBlueprintFunctionLibrary::AttributesConvertToString(FAttributes Attribute, bool & bSuccess)
{
	return ACastTo<FString, UStrProperty>(Attribute, bSuccess);
}
/*
FVector UAbilityBlueprintFunctionLibrary::AttributesConvertToVector(FAttributes Attribute, bool& bSuccess)
{
	return ACastToStruct<FVector>(Attribute, bSuccess);
}
*/
UObject * UAbilityBlueprintFunctionLibrary::AttributesConvertToObject(FAttributes Attribute, bool & bSuccess)
{
	return ACastTo<UObject*, UObjectProperty>(Attribute, bSuccess);
}

UClass * UAbilityBlueprintFunctionLibrary::AttributesConvertToUClass(FAttributes Attribute, bool & bSuccess)
{
	return Cast<UClass>(ACastTo<UObject*, UClassProperty>(Attribute, bSuccess));
}