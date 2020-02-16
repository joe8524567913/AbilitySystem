// Created by: ChengXinYuan
// Release year:2020.1


#include "Ability/AbilityBlackBoard.h"


int32 UAbilityBlackBoard::GetAttributeAsInt32(FAttributeName AttributeName, bool& bSuccess)
{
	return GetAttribute<int32, UIntProperty>(AttributeName, bSuccess);
}

float UAbilityBlackBoard::GetAttributeAsFloat(FAttributeName AttributeName, bool& bSuccess)
{
	return GetAttribute<float, UFloatProperty>(AttributeName, bSuccess);
}
/*
FVector UAbilityBlackBoard::GetAttributeAsVector(FAttributeName AttributeName, bool& bSuccess)
{
	return GetStructAttribute<FVector>(AttributeName, bSuccess);
}
*/
bool UAbilityBlackBoard::GetAttributeAsBool(FAttributeName AttributeName, bool& bSuccess)
{
	return GetAttribute<bool, UBoolProperty>(AttributeName, bSuccess);
}

uint8 UAbilityBlackBoard::GetAttributeAsEnum(FAttributeName AttributeName, bool& bSuccess)
{
	return GetAttribute<uint8, UByteProperty>(AttributeName, bSuccess);
}

FName UAbilityBlackBoard::GetAttributeAsName(FAttributeName AttributeName, bool& bSuccess)
{
	return GetAttribute<FName, UNameProperty>(AttributeName, bSuccess);
}

FString UAbilityBlackBoard::GetAttributeAsString(FAttributeName AttributeName, bool& bSuccess)
{
	return GetAttribute<FString, UStrProperty>(AttributeName, bSuccess);
}

UObject * UAbilityBlackBoard::GetAttributeAsObject(FAttributeName AttributeName, bool& bSuccess)
{
	return GetAttribute<UObject*, UObjectProperty>(AttributeName, bSuccess);
}

UClass * UAbilityBlackBoard::GetAttributeAsClass(FAttributeName AttributeName, bool& bSuccess)
{
	return Cast<UClass>(GetAttribute<UObject*, UClassProperty>(AttributeName, bSuccess));
}

void UAbilityBlackBoard::AddAttributesByProperty(FAttributeName AttributeName, UProperty * Property, void * PropertyAddress, bool bCallBack)
{
	FAttributes LastAttribute = *AttributesList.Find(AttributeName.Attribute);
	FAttributes Attributes;
	Attributes.AttributeProperty = Property;
	Attributes.AttributeAddress = PropertyAddress;
	AddAttributes(AttributeName, Attributes);
	/*
	if (OnAttributeChange.IsBound())
	{
		OnAttributeChange.Broadcast(AttributeName, LastAttribute, Attributes);
	}
	*/
}

