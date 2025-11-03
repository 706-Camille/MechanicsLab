// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Ability/MLAbilityBase.h"
#include "Character/MLCharacterBase.h"
#include "MLCombatComponent.generated.h"

class AMLCharacterBase;
class UMLAbilityBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatEventSignature, const FGameplayTag&, EventTag);

UENUM(Blueprintable)
enum class ECombatState : uint8
{
	Idle,
	Attacking
};

USTRUCT(Blueprintable)
struct FAttackInfo
{
	GENERATED_BODY()
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHANICSLAB_API UMLCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMLCombatComponent();

	/** Initialize Combat Actor Info when the component is registered */
	virtual void InitCombatActorInfo(AActor* InOwnerActor, APawn* InAvatarActor, AController* InController);

	/**
	 * 어빌리티 인스턴스가 실행을 완료하고 종료될 때(EndAbility 호출 시) 호출.
	 * 이 함수는 해당 어빌리티를 'ActiveAbilities' 배열에서 제거
	 *
	 * @param EndedAbility 종료되는 어빌리티 인스턴스에 대한 포인터
	*/
	void NotifyAbilityEnded(UMLAbilityBase* EndedAbility);

	
	/** AnimNotify, Overlap 등 어디서든 호출할 수 있는 "이벤트 발생" 함수 */
	UFUNCTION(BlueprintCallable, Category = "Combat|Events")
	void SendCombatEvent(FGameplayTag EventTag);
	


protected:
	//~ Begin UActorComponent Interface
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~ End UActorComponent Interface


	// Replication
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void InitializeDefaultAbilities();
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateAbilityByTag(const FGameplayTag& InAbilityTag);

	UFUNCTION(Server, Reliable)
	void ServerTryActivateAbilityByTag(const FGameplayTag& InAbilityTag);

	bool ActivateAbilityByTag_Internal(const FGameplayTag& InAbilityTag);
	

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_PlayAttackMontage(ACharacter* TargetCharacter, UAnimMontage* Montage, const float InPlayRate);
	
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void Multicast_PlayAttackMontage(ACharacter* TargetCharacter, UAnimMontage* Montage, const float InPlayRate);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	TArray<TSubclassOf<UMLAbilityBase>> AbilityClasses;
	
	UPROPERTY(Transient)
	TArray<TObjectPtr<UMLAbilityBase>> ActiveAbilities;
	
	FAbilityActorInfo ActorInfo;
	
	/**
	 * 모든 어빌리티가 Listen할 수 있는 델리게이트
	 */
	UPROPERTY(BlueprintAssignable, Category = "Combat|Events")
	FOnCombatEventSignature OnCombatEvent;
	
};

