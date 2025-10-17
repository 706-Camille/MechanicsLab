// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MLPlayerState.h"

#include "Component/MLAttributeComponent.h"
#include "Component/MLCombatComponent.h"


AMLPlayerState::AMLPlayerState()
{
	
}

void AMLPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// TODO
}
