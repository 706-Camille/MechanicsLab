// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MLWidgetController.h"
#include "MLOverlayWidgetController.generated.h"

/**
 * 
 */


UCLASS()
class MECHANICSLAB_API UMLOverlayWidgetController : public UMLWidgetController
{
	GENERATED_BODY()

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToAttributeComponent() override;
	
	
	
};
