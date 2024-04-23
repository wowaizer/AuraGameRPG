
#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;


void FAuraGameplayTags::InitializeNativeGameplayTags()
{


	//Vital attributes
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Vital.Health"),
			FString("Current amount of health"));


	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Vital.Mana"),
			FString("Current amount of mana"));



	//Primary attributes

	GameplayTags.Attributes_Primary_Strenght = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Primary.Strenght"),
			FString("Increases physical damage"));

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),
			FString("Increases magical damage"));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),
			FString("Increases armor and armor penetration"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),
			FString("Increases health"));

	//Secondary attributes


	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),
			FString("Maximum amount of health obtainable"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),
			FString("Maximum amount of mana obtainable"));

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),
			FString("Reduces damage taken,improves Block Chance"));

	GameplayTags.Attributes_ArmorPenetration = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),
			FString("Ignored procentage of enemy armor, Increases Critical Hit Chance"));

	GameplayTags.Attributes_BlockChance = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),
			FString("Chance to cut incoming damage to half"));

	GameplayTags.Attributes_CriticalHitChance = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),
			FString("Chance to double damage plus critical hit bonus"));

	GameplayTags.Attributes_CriticalHitDamage = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),
			FString("Bonus damage added when a critical hit is scored"));

	GameplayTags.Attributes_CriticalHitResistance = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),
			FString("Reduces critical hit chance of attacking enemies"));

	GameplayTags.Attributes_HealthRegeneration = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),
			FString("Amount of health regenerated in 1 second"));

	GameplayTags.Attributes_ManaRegeneration = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),
			FString("Amount of mana regenerated in 1 second"));

	//Ability Input

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("InputTag.LMB"),
			FString("Input tag for left mouse button"));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("InputTag.RMB"),
			FString("Input tag for right mouse button"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("InputTag.1"),
			FString("Input tag for 1 key  button"));

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("InputTag.2"),
			FString("Input tag for 2 key  button"));

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("InputTag.3"),
			FString("Input tag for 3 key  button"));

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("InputTag.4"),
			FString("Input tag for 4 key  button"));


	GameplayTags.Damage = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Damage"),
			FString("Tag for Damage"));

	//Damage Types

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Damage.Fire"),
			FString("Fire Damage Type"));

	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Damage.Lightning"),
			FString("Lightning Damage Type"));

	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Damage.Arcane"),
			FString("Arcane Damage Type"));

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Damage.Physical"),
			FString("Physical Damage Type"));


	//Resistances

	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Resistance.Fire"),
			FString("Fire Resistance Type"));

	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"),
			FString("Lightning Resistance Type"));

	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"),
			FString("Arcane Resistance Type"));

	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Attributes.Resistance.Physical"),
			FString("Physical Resistance Type"));


	//Attack abilities tags
	
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Abilities.Attack"),
			FString("Attack Ability Tag"));


	//Montage tags

	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Montage.Attack.Weapon"),
			FString("Weapon Tag"));

	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Montage.Attack.RightHand"),
			FString("RightHand Tag"));


	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Montage.Attack.LeftHand"),
			FString("LeftHand Tag"));

	//Map of Damage Types to Resistances


	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire,GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning,GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane,GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical,GameplayTags.Attributes_Resistance_Physical);

	//Effects

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().
		AddNativeGameplayTag(FName("Effects.HitReact"),
			FString("Tag granting when Hit Reacting"));
}
