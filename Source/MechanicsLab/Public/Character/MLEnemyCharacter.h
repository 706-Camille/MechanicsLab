// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MLCharacterBase.h"
#include "MLEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICSLAB_API AMLEnemyCharacter : public AMLCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

	virtual void InitCombatActorInfo() override;

public:
	/** Begin IEnemyInterface*/
	virtual UAnimMontage* GetHitReactMontage_Implementation() const override;
	/** End IEnemyInterface*/
protected:
	virtual void PossessedBy(AController* NewController) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> HitReactMontage;
};
