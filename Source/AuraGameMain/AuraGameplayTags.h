#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 * 
 * Singletone containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
	public:
		static const FAuraGameplayTags &Get() {return GameplayTags;}
		static void InitializeNativeGameplayTags();

		//Vital attributes
		FGameplayTag Attributes_Vital_Health;
		FGameplayTag Attributes_Vital_Mana;
		

		//Primary attributes
		FGameplayTag Attributes_Primary_Strenght;
		FGameplayTag Attributes_Primary_Intelligence;
		FGameplayTag Attributes_Primary_Resilience;
		FGameplayTag Attributes_Primary_Vigor;

		//Secondary attributes
		FGameplayTag Attributes_Secondary_MaxHealth;
		FGameplayTag Attributes_Secondary_MaxMana;
		FGameplayTag Attributes_Secondary_Armor;
		FGameplayTag Attributes_ArmorPenetration;
		FGameplayTag Attributes_BlockChance;
		FGameplayTag Attributes_CriticalHitChance;
		FGameplayTag Attributes_CriticalHitDamage;
		FGameplayTag Attributes_CriticalHitResistance;
		FGameplayTag Attributes_HealthRegeneration;
		FGameplayTag Attributes_ManaRegeneration;

		//Resistances
		FGameplayTag Attributes_Resistance_Fire;
		FGameplayTag Attributes_Resistance_Lightning;
		FGameplayTag Attributes_Resistance_Arcane;
		FGameplayTag Attributes_Resistance_Physical;

		//Ability Input
		FGameplayTag InputTag_LMB;
		FGameplayTag InputTag_RMB;
		FGameplayTag InputTag_1;
		FGameplayTag InputTag_2;
		FGameplayTag InputTag_3;
		FGameplayTag InputTag_4;

		FGameplayTag Damage;
		FGameplayTag Damage_Fire;
		FGameplayTag Damage_Lightning;
		FGameplayTag Damage_Arcane;
		FGameplayTag Damage_Physical;

		FGameplayTag Abilities_Attack;

		FGameplayTag Montage_Attack_Weapon;
		FGameplayTag Montage_Attack_RightHand;
		FGameplayTag Montage_Attack_LeftHand;

		TMap<FGameplayTag,FGameplayTag> DamageTypesToResistances;

		FGameplayTag Effects_HitReact;

	private:
		static FAuraGameplayTags GameplayTags;
};