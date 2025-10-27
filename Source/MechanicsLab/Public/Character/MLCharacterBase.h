// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "MLCharacterBase.generated.h"

class UMLAttributeComponent;
class UMLCombatComponent;

UCLASS()
class MECHANICSLAB_API AMLCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMLCharacterBase();

	/** Getter */
	FORCEINLINE UMLCombatComponent* GetCombatComponent() const { return CombatComponent; }
	FORCEINLINE UMLAttributeComponent* GetAttributeComponent() const { return AttributeComponent; }
	/** End Getter*/

	
	
	virtual void InitCombatActorInfo();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	/** Combat Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMLCombatComponent> CombatComponent;

	/** Attribute Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMLAttributeComponent> AttributeComponent;
	
		
};
