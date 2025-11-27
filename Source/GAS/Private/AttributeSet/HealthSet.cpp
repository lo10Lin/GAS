// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSet/HealthSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"


UHealthSet::UHealthSet()
{
	Health = 100;
	MaxHealth = 100;
	//Shield = 100;
	//MaxShield = 100;
	Stamina = 100;
	MaxStamina = 100;
}

void UHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, Shield, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, MaxShield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UHealthSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	//else if (Attribute == GetShieldAttribute())
	//{
	//	NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxShield());
	//}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}

}

void UHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());
	}
	//else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
	//{
	//	SetShield(GetShield());
	//}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(GetStamina());
	}

}

bool UHealthSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{

	return true;
}
