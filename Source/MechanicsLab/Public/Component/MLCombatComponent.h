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
	// Sets default values for this component's properties
	UMLCombatComponent();

	/** Initialize Combat Actor Info when the component is registered */
	virtual void InitCombatActorInfo(AActor* InOwnerActor, APawn* InAvatarActor, AController* InController);
	
	UFUNCTION(BlueprintCallable, Category="Combat")
	void ActivateAbilityByTag(FGameplayTag Tag);

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
	UPROPERTY()
	TArray<UMLAbilityBase*> Abilities;
	
	FAbilityActorInfo ActorInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	TArray<TSubclassOf<UMLAbilityBase>> AbilityClasses;
	
};

