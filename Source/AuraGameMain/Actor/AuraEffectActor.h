#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectAplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DontApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	
	RemovalOnEndOverlap,
	DontRemove
};

UCLASS()
class AURAGAMEMAIN_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();


	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	bool bDestroyOnEffectApplication = false;


	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	bool bApplyEffectsToEnemies = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	EEffectAplicationPolicy InstantEffectAplicationPolicy = EEffectAplicationPolicy::DontApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	EEffectAplicationPolicy DurationEffectAplicationPolicy = EEffectAplicationPolicy::DontApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	EEffectAplicationPolicy InfiniteEffectAplicationPolicy = EEffectAplicationPolicy::DontApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemovalOnEndOverlap;

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor *Target,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor *TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor *TargetActor);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects")
	float ActorLevel;

private:

};
