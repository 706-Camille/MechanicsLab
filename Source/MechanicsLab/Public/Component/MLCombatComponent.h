// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MLCombatComponent.generated.h"

class UMLAbilityBase;

UENUM(Blueprintable)
enum class ECombatState : uint8
{
	Idle,
	Attacking
};

USTRUCT(Blueprintable)
struct FAttackInfo
{
	GENERATED_BODY()
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHANICSLAB_API UMLCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMLCombatComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	TArray<UMLAbilityBase*> Abilities;

	UFUNCTION(BlueprintCallable, Category="Combat")
	void ActivateAbilityByTag(FGameplayTag Tag);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateAbility();
		
	
};
