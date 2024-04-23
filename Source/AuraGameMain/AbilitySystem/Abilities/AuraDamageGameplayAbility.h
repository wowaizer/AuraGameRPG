#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "AuraGameMain/Character/AuraCharacterBase.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor *TargetActor);

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>DamageEffecClass;

	UPROPERTY(EditDefaultsOnly,Category = "Damage")
	TMap<FGameplayTag,FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontage(const TArray<FTaggedMontage> &TaggedMontages) const;
	
};
