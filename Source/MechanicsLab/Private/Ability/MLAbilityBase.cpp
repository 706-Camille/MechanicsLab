// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/MLAbilityBase.h"

#include "Component/MLCombatComponent.h"
#include "GameFramework/Character.h"


UWorld* UMLAbilityBase::GetWorld() const
{
	if (ActorInfo.OwnerActor.IsValid())
	{
		return ActorInfo.OwnerActor->GetWorld();
	}
	return nullptr;
}

void UMLAbilityBase::InitializeAbility(const FAbilityActorInfo& InAbilityActorInfo)
{
	ActorInfo = InAbilityActorInfo;
}

void UMLAbilityBase::ActivateAbility_Implementation(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef)
{
}

void UMLAbilityBase::EndAbility_Implementation()
{
	if (ActorInfo.CombatComponent.IsValid() && ActorInfo.OwnerActor->HasAuthority())
	{
		// 델리게이트 바인딩을 완전히 해제
		ActorInfo.CombatComponent->OnCombatEvent.RemoveDynamic(this, &UMLAbilityBase::HandleCombatEvent);
		// CombatComponent가 이 인스턴스(this)를 ActiveAbilities 배열에서 제거하도록 요청
		ActorInfo.CombatComponent->NotifyAbilityEnded(this);
	}
}



UMLCombatComponent* UMLAbilityBase::GetCombatComponentFromActorInfo() const
{
	return ActorInfo.CombatComponent.Get();
}	

void UMLAbilityBase::HandleCombatEvent(const FGameplayTag& ReceivedTag)
{
	if (WaitingForEventTags.Contains(ReceivedTag))
	{
		// Blueprint에서 구현될 이벤트 콜백 
		EventReceived(ReceivedTag);
	}	
}


void UMLAbilityBase::WaitCombatEvent(FGameplayTag EventTagToWait)
{
	if (!ActorInfo.CombatComponent.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] WaitCombatEvent: CombatComponent is invalid."), *GetName());
		return;
	}

	if (!ActorInfo.OwnerActor->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] WaitCombatEvent: Client cannot wait for events."), *GetName());
		return;
	}

	WaitingForEventTags.Add(EventTagToWait);
	ActorInfo.CombatComponent->OnCombatEvent.AddDynamic(this, &UMLAbilityBase::HandleCombatEvent);
}

