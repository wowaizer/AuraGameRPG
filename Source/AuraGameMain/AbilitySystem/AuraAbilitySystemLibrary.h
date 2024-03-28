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
	static void GiveStartupAbilities(const UObject *WorldContextObjec,UAbilitySystemComponent *ASC);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject *WorldContextObjec);
};
