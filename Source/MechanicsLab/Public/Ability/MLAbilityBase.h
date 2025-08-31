// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"

#include "MLAbilityBase.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class MECHANICSLAB_API UMLAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	FGameplayTag AbilityTag;

	
	UFUNCTION(BlueprintCallable)
	virtual void Activate(ACharacter* OwnerCharacter)
	{
		
	}
	
};
