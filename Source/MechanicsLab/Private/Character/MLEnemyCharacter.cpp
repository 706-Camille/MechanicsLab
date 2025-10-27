// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MLEnemyCharacter.h"
#include "Component/MLCombatComponent.h"


void AMLEnemyCharacter::InitCombatActorInfo()
{
	CombatComponent->InitCombatActorInfo(this, this, GetController());
}

UAnimMontage* AMLEnemyCharacter::GetHitReactMontage_Implementation() const
{
	check(HitReactMontage);

	return HitReactMontage;
}

void AMLEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitCombatActorInfo();
}
