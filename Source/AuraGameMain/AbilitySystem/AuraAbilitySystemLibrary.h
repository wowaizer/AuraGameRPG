#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraGameMain/AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController *GetOverlayWidgetController(const UObject *WorldContextObject);

	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController *GetAttributeMenuWidgetController(const UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject *WorldContextObjec,ECharacterClass CharacterClass,
		float Level,UAbilitySystemComponent *ASC);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject *WorldContextObjec,UAbilitySystemComponent *ASC,ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject *WorldContextObjec);

	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayerswithinRadius(const UObject *WorldContextObject,TArray<AActor*>& OutOverlappingActors,
		TArray<AActor*> ActorsToIgnore,float Radius,const FVector &SphereOrigin);

	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriends(AActor *FirstActor,AActor *SecondActor);

	static int32 GetXPRewardForClassAndLevel (const UObject *WorldContextObject,ECharacterClass CharacterClass,int32 CharacterLevel);
};
