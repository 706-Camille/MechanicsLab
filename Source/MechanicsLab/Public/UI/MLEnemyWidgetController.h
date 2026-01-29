// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/MLAttributeComponent.h"
#include "UI/MLWidgetController.h"
#include "MLEnemyWidgetController.generated.h"

class UMLWidget;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)	
class MECHANICSLAB_API UMLEnemyWidgetController : public UMLWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BindCallbackToAttributes() override;
	
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamageTaken(const FDamageInfo& DamageInfo);
	
	void HandleDamageTaken(const FDamageInfo& DamageInfo);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UUserWidget> DamageWidgetClass;
	
protected:
	
public:
	
	
	
	
};
