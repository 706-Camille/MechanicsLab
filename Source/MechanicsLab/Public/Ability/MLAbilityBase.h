// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "MLAbilityBase.generated.h"


USTRUCT(BlueprintType)
struct FAbilityActorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<APawn> AvatarActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<AController> Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<class UMLCombatComponent> CombatComponent;	
};

USTRUCT(BlueprintType)
struct FAbilityDef
{
	GENERATED_BODY()

	/** What ability to grant */
	UPROPERTY(EditDefaultsOnly, Category="Ability Definition")
	TSubclassOf<UMLCombatComponent> Ability;

	FAbilityDef() : Ability(nullptr){};
	FAbilityDef(const TSubclassOf<UMLCombatComponent>& AbilityClass) : Ability(AbilityClass){};
};


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

	FAbilityActorInfo ActorInfo;

	void InitializeAbility(const FAbilityActorInfo& InAbilityActorInfo);
	
	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	void ActivateAbility(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef);
	
	virtual void ActivateAbility_Implementation(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef);

	UFUNCTION(BlueprintNativeEvent, Category = "Ability")
	void EndAbility(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef);

	virtual void EndAbility_Implementation(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	UMLCombatComponent* GetCombatComponentFromActorInfo() const;

};
