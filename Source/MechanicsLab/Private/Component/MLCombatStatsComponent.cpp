// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MLCombatStatsComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UMLCombatStatsComponent::UMLCombatStatsComponent()
{
}

void UMLCombatStatsComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, MaxHP);
	DOREPLIFETIME(ThisClass, HP);
}


void UMLCombatStatsComponent::OnRep_MaxHP()
{
	OnMaxHPChanged.Broadcast(MaxHP);
}

void UMLCombatStatsComponent::OnRep_HP()
{
	OnHPChanged.Broadcast(HP);
}
