// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Ability/MLAbilityBase.h"
#include "MLCombatComponent.generated.h"

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
	
	FAbilityActorInfo ActorInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	TArray<TSubclassOf<UMLAbilityBase>> AbilityClasses;

	UPROPERTY()
	TArray<UMLAbilityBase*> Abilities; 
	

	UFUNCTION(BlueprintCallable, Category="Combat")
	void ActivateAbilityByTag(FGameplayTag Tag);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Initialize Ability Actor Info when the component is registered */
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, APawn* InAvatarActor);

	//~ Begin UActorComponent Interface
	virtual void OnRegister() override;
	//~ End UActorComponent Interface

	void GrantAbility();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateAbilityByClass(TSubclassOf<UMLAbilityBase> InAbilityToActivate);
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool TryActivateAbilityByTag(const FGameplayTag& InAbilityTag);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
};

inline void UMLCombatComponent::OnRegister()
{
	Super::OnRegister();
	InitAbilityActorInfo(GetOwner(), Cast<APawn>(GetOwner()));
	GrantAbility();
}
