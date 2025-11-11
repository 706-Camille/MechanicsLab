// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MLOverlayWidgetController.h"

#include "Component/MLAttributeComponent.h"


void UMLOverlayWidgetController::BroadcastInitialValues()
{
	OnHPChanged.Broadcast(AttributeComponent->GetHP());
	OnMaxHPChanged.Broadcast(AttributeComponent->GetMaxHP());
	OnStrengthChanged.Broadcast(AttributeComponent->GetStrength());
}

void UMLOverlayWidgetController::BindCallbackToAttributes()
{
	checkf(AttributeComponent, TEXT("Missing AttributeComponent in UMLOverlayWidgetController"));

	AttributeComponent->OnMaxHPChanged.AddLambda([this](float Value)
		{
			OnMaxHPChanged.Broadcast(Value);
		}
	);

	AttributeComponent->OnHPChanged.AddLambda([this](float Value)
		{
			OnHPChanged.Broadcast(Value);
		}
	);
	
}
