
#include "AttributeMenuWidgetController.h"
#include "AuraGameMain/AbilitySystem/AuraAttributeSet.h"
#include "AuraGameMain/AbilitySystem/Data/AttributeInfo.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet *AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for(auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key,Pair.Value());
			}
	);
	}
	
}



void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet *AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for(auto& Pair : AS->TagsToAttributes)
	{

		BroadcastAttributeInfo(Pair.Key,Pair.Value());
		
	}
}


void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag &AttributeTag, const FGameplayAttribute &Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);

	AttributeInfoDelegate.Broadcast(Info);
}



