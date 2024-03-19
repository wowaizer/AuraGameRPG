#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURAGAMEMAIN_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	

	UOverlayWidgetController *GetOverlayWidgetController(const FWidgetControllerParams &WCParams);

	UAttributeMenuWidgetController *GetAttributeMenuWidgetController(const FWidgetControllerParams &WCParams);

	void InitOverlay(APlayerController *PC,APlayerState *PS,
		UAbilitySystemComponent *ASC,UAttributeSet * AS);


private:
	
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
