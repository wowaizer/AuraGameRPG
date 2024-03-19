
#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraGameMain/Interaction/EnemyInterface.h"
#include "AuraGameMain/UI/WidgetController/OverlayWidgetController.h"
#include "AuraGameMain/AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	//** Enemy Interface */
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	//** End Enemy Interface */

	//** Combat Interface */
	virtual int32 GetPlayerLevel() override;

	//** End Combat Interface */


	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	ECharacterClass CharacterClass  = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	
};
