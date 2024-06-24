#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
class ULevelUpInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged,int32 /* Stat Value */);
/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet *GetAttributeSet() const {return AttributeSet;}

	FOnPlayerStatChanged OnXpChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel() const {return Level;}
	FORCEINLINE int32 GetXP() const {return XP;}

	void AddToXP(int32 InXP);
	void AddToLevel (int32 InLevel);

	void SetXP(int32 InXP);
	void SetLevel (int32 InLevel);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo>LevelUpInfo;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 0;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);


	UFUNCTION()
	void OnRep_XP(int32 OldXP);
};
