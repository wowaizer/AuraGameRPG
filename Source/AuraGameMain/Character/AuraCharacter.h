
#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"


/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

	public:
		AAuraCharacter();

		virtual void PossessedBy(AController *NewController) override;
		virtual void OnRep_PlayerState() override;

		//** Combat Interface */
		virtual int32 GetPlayerLevel() override;

		//** End Combat Interface */



protected:
	virtual void BeginPlay() override;
	
private:
	virtual void InitAbilityActorInfo() override;
	
};
