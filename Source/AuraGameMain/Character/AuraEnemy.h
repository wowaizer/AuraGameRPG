
#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraGameMain/Interaction/EnemyInterface.h"
#include "AuraGameMain/UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"


class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;
/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	virtual void PossessedBy(AController *NewController) override;

	//** Enemy Interface */
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	//** End Enemy Interface */

	//** Combat Interface */
	virtual int32 GetPlayerLevel() override;

	
	virtual void HitReaction_Implementation(bool IsHit); //Add this to fix the problem with Enemy HitReaction. Using in Combat Intetface
																		  //Realization in CPP file, but fires in BP 
	virtual void Die() override;

	virtual void SetCombatTarget_Implementation(AActor *InCombatTarget) override;
	virtual AActor *GetCombatTarget_Implementation() const override;
	//** End Combat Interface */


	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UFUNCTION()
	void HitReactTagChanged(const FGameplayTag TagChange, int32 NewCount);
	
	void OnOwnerTagChange(FGameplayTag TagChange, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;


	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite,Category = "Combat")
	TObjectPtr<AActor>CombatTarget;

protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	int32 Level = 1;



	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;


	UPROPERTY(EditAnywhere,Category = "AI")
	TObjectPtr<UBehaviorTree>BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAuraAIController>AuraAIController;
};
