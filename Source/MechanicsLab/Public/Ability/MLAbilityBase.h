// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "MLAbilityBase.generated.h"



USTRUCT(BlueprintType)
struct FAbilityActorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<APawn> AvatarActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<AController> Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	TWeakObjectPtr<class UMLCombatComponent> CombatComponent;	
};

USTRUCT(BlueprintType)
struct FAbilityDef
{
	GENERATED_BODY()

	/** What ability to grant */
	UPROPERTY(EditDefaultsOnly, Category="Ability Definition")
	TSubclassOf<UMLAbilityBase> AbilityClass;

	FAbilityDef() : AbilityClass(nullptr){};
	FAbilityDef(const TSubclassOf<UMLAbilityBase>& AbilityClass) : AbilityClass(AbilityClass){};
};


/**
 * 
 */
UCLASS(Blueprintable)
class MECHANICSLAB_API UMLAbilityBase : public UObject
{
	GENERATED_BODY()



public:
	virtual UWorld* GetWorld() const override;

	void InitializeAbility(const FAbilityActorInfo& InAbilityActorInfo);

	/**
	* 어빌리티를 실핸한다. C++과 블루프린트 모두에서 구현 가능
	* 블루프린트에서 'Event Activate Ability'로 Override 할 수 있다.
	* @param InActorInfo 어빌리티를 실행하는 액터의 정보.
	* @param InAbilityDef 이 어빌리티의 기본 정의
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	void ActivateAbility(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef);
	
	virtual void ActivateAbility_Implementation(const FAbilityActorInfo& InActorInfo, const FAbilityDef& InAbilityDef);

	/**
	* 어빌리티 실행을 종료하고 관련 리소스(델리게이트 등)를 정리합니다.
	* C++과 블루프린트 모두에서 구현되며, 블루프린트에서 호출 가능합니다.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void EndAbility();

	virtual void EndAbility_Implementation();

	//* convenience function For 어빌리티 구현 */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	UMLCombatComponent* GetCombatComponentFromActorInfo() const;

protected:

	/**
	 * [C++ 전용 콜백]
	 * CombatComponent의 OnCombatEvent 델리게이트에 바인딩될 C++ 내부 함수
	 * 이 함수가 블루프린트의 'EventReceived'를 호출
	 */
	UFUNCTION()
	void HandleCombatEvent(const FGameplayTag& ReceivedTag);
	/**
	 * [블루프린트 호출 가능] 
	 * 어빌리티 BP에서 이 함수를 호출하여 'EventTag'가 발생할 때까지 대기 상태
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability|Events")
	void WaitCombatEvent(FGameplayTag EventTagToWait);

	/**
	 * [블루프린트 구현]
	 * 'WaitCombatEvent'로 구독한 이벤트가 수신되면, C++이 이 이벤트를 호출
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability|Events")
	void EventReceived(const FGameplayTag& ReceivedTag);


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	FGameplayTag AbilityTag;

	UPROPERTY(BlueprintReadOnly, Category="Ability")
	FAbilityActorInfo ActorInfo;

	UPROPERTY()
	TArray<FGameplayTag> WaitingForEventTags;
	
	
};
