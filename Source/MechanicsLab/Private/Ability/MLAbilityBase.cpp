// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/MLAbilityBase.h"

#include "GameFramework/Character.h"


void UMLAbilityBase::InitializeAbility(const FAbilityActorInfo& InAbilityActorInfo)
{
	ActorInfo = InAbilityActorInfo;
}

void UMLAbilityBase::ActivateAbility_Implementation(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef)
{
}

void UMLAbilityBase::EndAbility_Implementation(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef)
{
}



UMLCombatComponent* UMLAbilityBase::GetCombatComponentFromActorInfo() const
{
	return ActorInfo.CombatComponent.Get();
}

