// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SendCombatEvent.h"

#include "Component/MLCombatComponent.h"


void UAnimNotify_SendCombatEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!EventTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimNotify_SendCombatEvent: EventTag가 설정되지 않았습니다."));
		return;
	}

	if (AActor* OwnerActor = MeshComp->GetOwner())
	{
		if (UMLCombatComponent* CombatComponent = OwnerActor->FindComponentByClass<UMLCombatComponent>())
		{
			// CombatComponent의 함수를 호출하여 이벤트를 전송
			CombatComponent->SendCombatEvent(EventTag);
		}
	}

	
	
	
}
