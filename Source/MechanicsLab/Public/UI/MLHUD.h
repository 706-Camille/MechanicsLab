// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MLHUD.generated.h"

class UMLWidget;
class UMLWidgetController;
class UMLAttributeComponent;
class UMLCombatComponent;
class UMLOverlayWidgetController;


/**
 * 
 */
UCLASS()
class MECHANICSLAB_API AMLHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UMLWidget> OverlayWidget;
	
	UMLOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams);
	void InitOverlay(
		APlayerController* InPlayerController,
		APlayerState* InPlayerState,
		UMLCombatComponent* InCombatComponent,
		UMLAttributeComponent* InAttributeComponent
	);

	

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMLWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMLWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMLOverlayWidgetController> OverlayWidgetController;
	
	
	
};
