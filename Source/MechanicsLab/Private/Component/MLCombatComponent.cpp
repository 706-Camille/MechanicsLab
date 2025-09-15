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
			
			Ability->ActivateAbility(ActorInfo, FAbilityDef(Ability->GetClass()));
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

void UMLCombatComponent::InitAbilityActorInfo(AActor* InOwnerActor, APawn* InAvatarActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "InitAbilityActorInfo");
	
	ActorInfo.OwnerActor = InOwnerActor;
	ActorInfo.AvatarActor = InAvatarActor;
	ActorInfo.CombatComponent = MakeWeakObjectPtr(this);
	ActorInfo.Controller = nullptr;
}


void UMLCombatComponent::GrantAbility()
{

	for (TSubclassOf<UMLAbilityBase> AbilityClass : AbilityClasses)
	{
		if (!AbilityClass) continue;

		UMLAbilityBase* Ability = NewObject<UMLAbilityBase>(this, AbilityClass);
		Ability->ActorInfo = ActorInfo;

		Abilities.Add(Ability);
	}
 
}


bool UMLCombatComponent::TryActivateAbilityByClass(TSubclassOf<UMLAbilityBase> InAbilityToActivate)
{
	if (InAbilityToActivate)
	{
		UMLAbilityBase* AbilityToActivate = CastChecked<UMLAbilityBase>(InAbilityToActivate);
		AbilityToActivate->ActivateAbility(ActorInfo, FAbilityDef(InAbilityToActivate->GetClass()));
	}

	return true;
}


bool UMLCombatComponent::TryActivateAbilityByTag(const FGameplayTag& InAbilityTag)
{
	for (UMLAbilityBase* Ability : Abilities)
	{
		if (Ability && Ability->AbilityTag.MatchesTagExact(InAbilityTag))
		{
			
			Ability->ActivateAbility(ActorInfo,FAbilityDef(Ability->GetClass()));
			return true;
		}
	}

	return false;
}

// Called every frame
void UMLCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

