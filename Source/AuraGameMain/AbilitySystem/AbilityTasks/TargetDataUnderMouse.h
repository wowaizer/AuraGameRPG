#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,const FGameplayAbilityTargetDataHandle&, DataHandle);
/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(DisplayName = "TargetDataUnderMouse",BlueprintCallable, Category = "AbilityTasks", meta = (HidePin = "OwningAbility",
		DefaultToSelf = "OwningAbility",BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse *CreateTargetDataUnderMouse(UGameplayAbility *OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:

	virtual void Activate() override;
	void SendMouseCursorData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle &DataHandle,FGameplayTag ActivationTag);
};
