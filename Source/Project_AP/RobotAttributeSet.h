// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RobotAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API URobotAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData AutoMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData UltimateMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData AutoManaRegen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData UltimateManaRegen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData AutoManaMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData UltimateManaMax;

public:
	// 게임플레이 이펙트의 결과
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	// void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, Health);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, MaxHealth);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(Speed);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Speed);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Speed);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, Speed);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(AutoMana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(AutoMana);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(AutoMana);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, AutoMana);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(UltimateMana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(UltimateMana);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(UltimateMana);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, UltimateMana);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(AutoManaRegen);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(AutoManaRegen);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(AutoManaRegen);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, AutoManaRegen);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(UltimateManaRegen);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(UltimateManaRegen);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(UltimateManaRegen);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, UltimateManaRegen);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(AutoManaMax);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(AutoManaMax);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(AutoManaMax);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, AutoManaMax);

	GAMEPLAYATTRIBUTE_VALUE_GETTER(UltimateManaMax);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(UltimateManaMax);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(UltimateManaMax);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URobotAttributeSet, UltimateManaMax);


};
