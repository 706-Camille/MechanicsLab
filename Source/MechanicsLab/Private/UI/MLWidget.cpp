// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MLWidget.h"


void UMLWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
