// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MLWidgetController.generated.h"

class UMLCombatComponent;
class UMLAttributeComponent;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController* PC,
		APlayerState* PS,
		UMLCombatComponent* CC,
		UMLAttributeComponent* AC)
	: PlayerController(PC), PlayerState(PS), CombatComponent(CC), AttributeComponent(AC) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMLCombatComponent> CombatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMLAttributeComponent> AttributeComponent;
	
};
UCLASS()
class MECHANICSLAB_API UMLWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues();
	virtual void BindCallbackToAttributes();
	void SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams);
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMLCombatComponent* CombatComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMLAttributeComponent* AttributeComponent = nullptr;


	
	
};
