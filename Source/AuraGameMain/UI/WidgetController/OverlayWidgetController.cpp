#include "OverlayWidgetController.h"
#include "AuraGameMain/AbilitySystem/AuraAttributeSet.h"
#include "AuraGameMain/AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameMain/Character/AuraCharacter.h"
#include "AuraGameMain/AbilitySystem/Data/AbilityInfo.h"
#include <AuraGameMain/Player/AuraPlayerState.h>
#include "AuraGameMain/AbilitySystem/Data/LevelUpInfo.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	AAuraPlayerState *AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnXpChangedDelegate.AddUObject(this,&UOverlayWidgetController::OnXpChanged);

	const UAuraAttributeSet *AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);


	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth()); 
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet *AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{	
			OnHealthChanged.Broadcast(Data.NewValue);
		
		}
	

	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{	
			OnMaxHealthChanged.Broadcast(Data.NewValue);

		}

	);


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{	
			OnManaChanged.Broadcast(Data.NewValue);

		}

	);


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{	
			OnMaxManaChanged.Broadcast(Data.NewValue);

		}

	);


	if(UAuraAbilitySystemComponent *AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if(AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
			
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this,&UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		

		AuraASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer &AssetTags)
			{
				for (const FGameplayTag &Tag : AssetTags)
				{
					//"A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

					if(Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow *Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}

				}
			}
		);

	}

		
	


	//Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	//	[this](const FGameplayTagContainer &AssetTags)
	//	{

	//		for (const FGameplayTag &Tag : AssetTags)
	//		{
	//			//"A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
	//			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

	//			if(Tag.MatchesTag(MessageTag))
	//			{
	//				const FUIWidgetRow *Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
	//				MessageWidgetRowDelegate.Broadcast(*Row);
	//			}
	//			
	//		}
	//	}
	//);

}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent *AuraAbilitySystemComponent)
{

	//TODO Get information about all given abilities, look up their Ability Info and Broadcasted it to widgets

	if(!AuraAbilitySystemComponent->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;

	BroadcastDelegate.BindLambda([this,AuraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
			
			//TODO: need a way to figure out the ability tag for a given ability spec
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
	}
	);

	AuraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXpChanged(int32 NewXP) const
{
	const AAuraPlayerState *AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	const ULevelUpInfo *LevelUpInfo = AuraPlayerState->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out AuraPlayerState BP"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);

	const int32 MaxLevel = LevelUpInfo->LevelUpInfomation.Num();

	if(Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfomation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInfomation[Level-1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;

		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}


}

