// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLAttributeComponent.generated.h"


#define MAKE_GETTER_AND_SETTER(Type, Name)       \
	public:									     \
	const Type& Get##Name() const { return Name;}\
	void Set##Name(const Type& Value) { Name = Value; }

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaxHPChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStrengthChanged, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHANICSLAB_API UMLAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	UMLAttributeComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void OnRep_MaxHP();
	UFUNCTION()
	void OnRep_HP();
	UFUNCTION()
	void OnRep_Strength();
	
public:
	/* Attributes Getter */
	const float& GetBaseMaxHP() const {return BaseMaxHP;} 
	const float& GetMaxHP() const {return MaxHP;}
	const float& GetBaseHP() const {return BaseHP;}
	const float& GetHP() const {return HP;}
	const float& GetBaseStrength() const {return BaseStrength;}
	const float& GetStrength() const {return Strength;}
	
	/* Attributes Setter */
	void SetBaseMaxHP(const float& Value){BaseMaxHP = Value;}
	void SetMaxHP(const float& Value){MaxHP = Value;}
	void SetBaseHP(const float& Value){BaseHP = Value;}
	void SetHP(const float& Value){HP = Value;}
	void SetBaseStrength(const float& Value){BaseStrength = Value;}
	void SetStrength(const float& Value){Strength = Value;}

protected:
		
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseMaxHP;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHP, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float MaxHP;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseHP;
	
	UPROPERTY(ReplicatedUsing = OnRep_HP, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float HP;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseStrength;

	UPROPERTY(ReplicatedUsing = OnRep_Strength, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float Strength;
	

public:
	FOnMaxHPChanged OnMaxHPChanged;
	FOnHPChanged OnHPChanged;
	FOnHPChanged OnStrengthChanged;
	
};
