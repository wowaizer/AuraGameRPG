
#include "AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AuraGameMain/UI/HUD/AuraHUD.h"
#include "AuraGameMain/Player/AuraPlayerState.h"
#include "AuraGameMain/Game/AuraGameModeBase.h"
#include "AbilitySystemComponent.h"
#include "AuraGameMain/UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if(APlayerController *PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if(AAuraHUD *AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState *PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent *ASC = PS->GetAbilitySystemComponent();
			UAttributeSet *AS = PS->GetAttributeSet();
			
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);

			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}

	}
	return nullptr;

}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if(APlayerController *PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if(AAuraHUD *AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState *PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent *ASC = PS->GetAbilitySystemComponent();
			UAttributeSet *AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);

			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}

	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject *WorldContextObjec,ECharacterClass CharacterClass,
	float Level,UAbilitySystemComponent *ASC)
{
	
	AActor *AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo *ClassInfo = GetCharacterClassInfo(WorldContextObjec);

	FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = 
		ASC->MakeEffectContext();

	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = 
		ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,PrimaryAttributesContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());


	FGameplayEffectContextHandle SecondaryAttributesContextHandle = 
		ASC->MakeEffectContext();

	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);


	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = 
		ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes,Level,SecondaryAttributesContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());



	FGameplayEffectContextHandle VitalAttributesContextHandle = 
		ASC->MakeEffectContext();

	VitalAttributesContextHandle.AddSourceObject(AvatarActor);


	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = 
		ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes,Level,VitalAttributesContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());

}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObjec, UAbilitySystemComponent* ASC)
{


	UCharacterClassInfo *ClassInfo = GetCharacterClassInfo(WorldContextObjec);

	for (auto AbilityClass : ClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObjec)
{
	AAuraGameModeBase *AuraGameMode = 
		Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObjec));
	if(AuraGameMode == nullptr) return nullptr;

	return AuraGameMode->CharacterClassInfo;

	 
}
