
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURAGAMEMAIN_API IEnemyInterface
{
	GENERATED_BODY()

public:
	virtual void HighLightActor() = 0;
	virtual void UnHighLightActor() = 0;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetCombatTarget(AActor *InCombatTarget);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor *GetCombatTarget() const;
};
