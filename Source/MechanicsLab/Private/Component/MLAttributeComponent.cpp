// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MLAttributeComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UMLAttributeComponent::UMLAttributeComponent()
{
	SetIsReplicatedByDefault(true);
}

void UMLAttributeComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, MaxHP);
	DOREPLIFETIME(ThisClass, HP);
}


void UMLAttributeComponent::OnRep_MaxHP()
{
	OnMaxHPChanged.Broadcast(GetMaxHP());
}

void UMLAttributeComponent::OnRep_HP()
{
	OnHPChanged.Broadcast(GetHP());
}

void UMLAttributeComponent::OnRep_Strength()
{
	OnStrengthChanged.Broadcast(GetStrength());
}
