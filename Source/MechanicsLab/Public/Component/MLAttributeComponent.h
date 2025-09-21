// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLAttributeComponent.generated.h"


#define MAKE_GETTER_AND_SETTER(Type, Name)       \
	public:									     \
	const Type& Get##Name() const { return Name;}\
	void Set##Name(const Type& Value) { Name = Value; }

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHPChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrengthChanged, float, NewValue);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHANICSLAB_API UMLAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	MAKE_GETTER_AND_SETTER(float, BaseMaxHP);
	MAKE_GETTER_AND_SETTER(float, MaxHP);
	MAKE_GETTER_AND_SETTER(float, BaseHP);
	MAKE_GETTER_AND_SETTER(float, HP);
	MAKE_GETTER_AND_SETTER(float, BaseStrength);
	MAKE_GETTER_AND_SETTER(float, Strength);
	

public:
	UMLAttributeComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRep_MaxHP();
	UFUNCTION()
	void OnRep_HP();
	UFUNCTION()
	void OnRep_Strength();

protected:
		
	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseMaxHP;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHP, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float MaxHP;


	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseHP;
	
	UPROPERTY(ReplicatedUsing = OnRep_HP, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float HP;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseStrength;

	UPROPERTY(ReplicatedUsing = OnRep_Strength, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float Strength;
	

public:
	UPROPERTY(BlueprintAssignable)
	FOnMaxHPChanged OnMaxHPChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnHPChanged OnHPChanged;

	UPROPERTY(BlueprintAssignable)
	FOnHPChanged OnStrengthChanged;
	
};
