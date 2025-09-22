// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MLOverlayWidgetController.h"

#include "Component/MLAttributeComponent.h"


void UMLOverlayWidgetController::BroadcastInitialValues()
{
	
}

void UMLOverlayWidgetController::BindCallbackToAttributeComponent()
{
	checkf(AttributeComponent, TEXT("Missing AttributeComponent in UMLOverlayWidgetController"));

	// TODO : 속성들 콜백함수 연결
}
