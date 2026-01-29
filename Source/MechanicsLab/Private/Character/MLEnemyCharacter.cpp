// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MLEnemyCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Component/MLCombatComponent.h"
#include "UI/MLEnemyWidgetController.h"


void AMLEnemyCharacter::InitCombatActorInfo()
{
	checkf(WidgetControllerClass, TEXT("WidgetControllerClass is null, It is assigned in EnemyCharacter"));
	CombatComponent->InitCombatActorInfo(this, this, GetController());
	
	WidgetController = NewObject<UMLEnemyWidgetController>(this, WidgetControllerClass);
	const FEnemyWidgetControllerParams WidgetControllerParams(this, CombatComponent, AttributeComponent);
	WidgetController->SetWidgetControllerParams(WidgetControllerParams);
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
