// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MLPlayerState.generated.h"

class UMLCombatComponent;
class UMLAttributeComponent;
/**
 * 
 */
UCLASS()
class MECHANICSLAB_API AMLPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AMLPlayerState();
	
	

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	

	
};
