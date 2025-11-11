// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MLHUD.h"
#include "UI/MLWidget.h"
#include "UI/MLWidgetController.h"
#include "UI/MLOverlayWidgetController.h"



UMLOverlayWidgetController* AMLHUD::GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams)
{
	
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UMLOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(InWidgetControllerParams);
	}

	return OverlayWidgetController;
}

void AMLHUD::InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState,
	UMLCombatComponent* InCombatComponent, UMLAttributeComponent* InAttributeComponent)
{
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is null, It is assigned in BP_MLHUD"));
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is null, It is assigned in BP_MLHUD"));


	UUserWidget* Widget =  CreateWidget<UUserWidget>(InPlayerController, OverlayWidgetClass);
	OverlayWidget = Cast<UMLWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(InPlayerController, InPlayerState, InCombatComponent,InAttributeComponent);
	OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}


