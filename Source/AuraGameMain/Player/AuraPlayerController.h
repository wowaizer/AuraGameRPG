#pragma once

#include "AuraGameMain/AuraGameplayTags.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"



class UDamageTextComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class USplineComponent;
/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client,Reliable)
	void ShowDamageNumber (float DamageAmount, ACharacter *TargetCharacter);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent () override;

private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed() {bShiftKeyDown = true;};
	void ShiftReleased() {bShiftKeyDown = false;};
	bool bShiftKeyDown = false;


	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	FHitResult CursorHit;
	IEnemyInterface *LastActor;
	IEnemyInterface *ThisActor; 

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig>InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent>AuraAbilitySystemComponent;
	
	 UAuraAbilitySystemComponent *GetASC();

	 FVector CashedDestination = FVector::ZeroVector;
	 float FollowTime = 0.f;
	 float ShortPressTreshold = 0.5f;
	 bool bAutoRunning = false;
	 bool bTargeting = false;

	 UPROPERTY(EditDefaultsOnly)
	 float AutoRunAcceptanceRadius = 50.f;

	 UPROPERTY(VisibleAnywhere)
	 TObjectPtr<USplineComponent> Spline;

	 void AutoRun();

	//UPROPERTY()
	//TObjectPtr<IEnemyInterface>LastActor;

	//UPROPERTY()
	//TObjectPtr<IEnemyInterface>ThisActor; 

	 UPROPERTY(EditDefaultsOnly)
	 TSubclassOf<UDamageTextComponent>DamageTextComponentClass;
};
