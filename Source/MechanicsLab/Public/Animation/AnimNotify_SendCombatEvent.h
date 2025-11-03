// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SendCombatEvent.generated.h"


/**
 * 
 */
UCLASS()
class MECHANICSLAB_API UAnimNotify_SendCombatEvent : public UAnimNotify
{
	GENERATED_BODY()
public:
	/**
	 * 이 Notify가 발생시킬(Broadcast) 이벤트 태그
	 * 몽타주 에디터의 Details 패널에서 이 태그를 선택할 수 있습니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimNotify")
	FGameplayTag EventTag;

	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	
	
};
