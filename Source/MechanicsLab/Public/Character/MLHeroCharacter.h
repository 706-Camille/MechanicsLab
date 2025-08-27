// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MLCharacterBase.h"
#include "MLHeroCharacter.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UMLCombatComponent;
/**
 * 
 */
UCLASS()
class MECHANICSLAB_API AMLHeroCharacter : public AMLCharacterBase
{
	GENERATED_BODY()

public:
	AMLHeroCharacter();
	TObjectPtr<UInputMappingContext> GetMappingContext() {return InputMappingContext;}

protected:


	virtual void PossessedBy(AController* NewController) override;
	/* Input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Zoom(const FInputActionValue& InputActionValue);
	void StartSprint(const FInputActionValue& InputActionValue);
	void EndSprint(const FInputActionValue& InputActionValue);
	/* Input */

	bool bSprint = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed = 600.0f;
	

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float MinZoomLength = 300.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float MaxZoomLength = 1000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
	float ZoomSpeed = 1.f;

	UPROPERTY()
	TObjectPtr<UMLCombatComponent> CombatComponent;
	
	
};
