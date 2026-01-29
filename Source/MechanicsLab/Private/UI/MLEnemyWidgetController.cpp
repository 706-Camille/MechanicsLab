// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MLEnemyWidgetController.h"

#include "Blueprint/UserWidget.h"
#include "Component/MLAttributeComponent.h"


void UMLEnemyWidgetController::BindCallbackToAttributes()
{
	//checkf(AttributeComponent, TEXT("Missing AttributeComponent in UMLEnemyWidgetController"));
	
	//AttributeComponent->OnDamageTaken.AddUObject(this, &UMLEnemyWidgetController::HandleDamageTaken);
}

void UMLEnemyWidgetController::HandleDamageTaken(const FDamageInfo& DamageInfo)
{
	/*
	if (DamageWidgetClass)
	{
		
		if (UUserWidget* DamageWidget = CreateWidget<UUserWidget>(GetWorld(), DamageWidgetClass))
		{
			DamageWidget->AddToViewport();
		}
	}
	*/
}

