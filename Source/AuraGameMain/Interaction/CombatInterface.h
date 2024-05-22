#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAnimMontage *Montage = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag SocketTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	USoundBase *ImpactSound = nullptr;
};



UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UAnimMontage;
/**
 * 
 */
class AURAGAMEMAIN_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag &MontageTag);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable) //Add this to fix the problem with Enemy HitReaction. 
	void HitReaction(bool IsHit);                     //Realization in AuraEnemy Class, but fires in BP 

	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor *GetAvatar();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontages();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UNiagaraSystem *GetBloodEffect();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FTaggedMontage GetTaggedMontage(const FGameplayTag &MontageTag);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	int32 GetMinionCount();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void IncrementMinionCount(int32 Amount);
};
