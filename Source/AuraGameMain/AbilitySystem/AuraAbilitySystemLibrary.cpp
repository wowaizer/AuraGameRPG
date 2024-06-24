
#include "AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AuraGameMain/UI/HUD/AuraHUD.h"
#include "AuraGameMain/Player/AuraPlayerState.h"
#include "AuraGameMain/Game/AuraGameModeBase.h"
#include "AbilitySystemComponent.h"
#include "AuraGameMain/UI/WidgetController/AuraWidgetController.h"
#include <AuraGameMain/AuraAbilityTypes.h>
#include <AuraGameMain/Interaction/CombatInterface.h>

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

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObjec, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass)
{


	UCharacterClassInfo *ClassInfo = GetCharacterClassInfo(WorldContextObjec);

	if(ClassInfo == nullptr) return;

	for (auto AbilityClass : ClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		ASC->GiveAbility(AbilitySpec);
	}

	const FCharacterClassDefaultInfo &DefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	for(auto AbilityClass : DefaultInfo.StartupAbilities)
	{
		ICombatInterface *CombatInterface  = Cast<ICombatInterface>(ASC->GetAvatarActor());
		if(CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObjec)
{
	AAuraGameModeBase *AuraGameMode = 
		Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObjec));
	if(AuraGameMode == nullptr) return nullptr;

	return AuraGameMode->CharacterClassInfo;

	 
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{

	if(const FAuraGameplayEffectContext *AuraContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FAuraGameplayEffectContext *AuraContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraContext->IsCricalHit();
	}
	return false;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{

	if(FAuraGameplayEffectContext *AuraContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraContext->SetIsBlockedHit(bInIsBlockedHit);
	}

}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if(FAuraGameplayEffectContext *AuraContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAuraAbilitySystemLibrary::GetLivePlayerswithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors,
	TArray<AActor*> ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{

	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			
			if(Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(Overlap.GetActor());
			}
		
		}
	}
}

bool UAuraAbilitySystemLibrary::IsNotFriends(AActor* FirstActor, AActor* SecondActor)
{

	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));

	const bool bBothAreEnemies =  FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));

	const bool bFriends = bBothArePlayers || bBothAreEnemies;

	return !bFriends;
}

int32 UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject, 
	ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo *ClassInfo = GetCharacterClassInfo(WorldContextObject);

	if(ClassInfo == nullptr) return 0;

	const FCharacterClassDefaultInfo Info = ClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);

	return static_cast <int32>(XPReward);


}
