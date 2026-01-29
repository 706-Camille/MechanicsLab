// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MLWidgetController.h"

#include "Component/MLAttributeComponent.h"
#include "PLayer/MLPlayerController.h"
#include "Player/MLPlayerState.h"
#include "Component/MLCombatComponent.h"


void UMLWidgetController::BroadcastInitialValues()
{
}

void UMLWidgetController::BindCallbackToAttributes()
{
}

void UMLWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams)
{
	PlayerController = InWidgetControllerParams.PlayerController;
	PlayerState = InWidgetControllerParams.PlayerState;
	CombatComponent = InWidgetControllerParams.CombatComponent;
	AttributeComponent = InWidgetControllerParams.AttributeComponent;
}

void UMLWidgetController::SetWidgetControllerParams(const FEnemyWidgetControllerParams& InWidgetControllerParams)
{
	OwnerActor = InWidgetControllerParams.EnemyActor;
	CombatComponent = InWidgetControllerParams.CombatComponent;
	AttributeComponent = InWidgetControllerParams.AttributeComponent;
}
