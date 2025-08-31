// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MLCombatComponent.h"
#include "Ability/MLAbilityBase.h"
#include "NativeGameplayTags.h"
#include "Character/MLCharacterBase.h"


// Sets default values for this component's properties
UMLCombatComponent::UMLCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UMLCombatComponent::ActivateAbilityByTag(FGameplayTag Tag)
{
	for (UMLAbilityBase* Ability : Abilities)
	{
		if (Ability && Ability->AbilityTag == Tag)
		{
			// 쿨다운, 스태미나 체크 등 추가 가능
			Ability->Activate(Cast<AMLCharacterBase>(GetOwner()));
			break;
		}
	}
}

// Called when the game starts
void UMLCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMLCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMLCombatComponent::ActivateAbility()
{
	
}

