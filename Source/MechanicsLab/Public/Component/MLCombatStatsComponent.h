// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLCombatStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHPChanged, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHANICSLAB_API UMLCombatStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMLCombatStatsComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRep_MaxHP();
	UFUNCTION()
	void OnRep_HP();

protected:

		
	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float BaseMaxHP;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHP, EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHP;


	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float BaseHP;
	
	UPROPERTY(ReplicatedUsing = OnRep_HP, EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float HP;

public:
	UPROPERTY(BlueprintAssignable)
	FOnMaxHPChanged OnMaxHPChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnHPChanged OnHPChanged;
	
};
