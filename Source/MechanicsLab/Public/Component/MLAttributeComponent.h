// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MLAttributeComponent.generated.h"


#define MAKE_GETTER_AND_SETTER(Type, Name)       \
	public:									     \
	const Type& Get##Name() const { return Name;}\
	void Set##Name(const Type& Value) { Name = Value; }

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float DamageScale;
	
	UPROPERTY(BlueprintReadWrite)
	float FinalDamage = 0.f;
	
	UPROPERTY(BlueprintReadWrite)
	AActor* Instigator;
	
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsCritical = false;
	
	FDamageInfo(float InDamageScale = 1.0f, AActor* InInstigator = nullptr)
		: DamageScale(InDamageScale), Instigator(InInstigator)
	{}
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, const FDamageInfo&);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHANICSLAB_API UMLAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	UMLAttributeComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * Replication Callback Functions
	 * 서버에서 속성이 변경될 때 클라이언트에 동기화되어 호출됨
	 * UI 갱신, 델리게이트 브로드캐스트 등 후처리를 담당
	*/
	UFUNCTION()
	void OnRep_MaxHP();
	UFUNCTION()
	void OnRep_HP();
	UFUNCTION()
	void OnRep_Strength();
	UFUNCTION()
	void OnRep_Damage();
	UFUNCTION()
	void OnRep_Defense();
	UFUNCTION()
	void OnRep_CriticalChance();
	
	
public:
	/* Attributes Getter */
	const float& GetBaseMaxHP() const {return BaseMaxHP;} 
	const float& GetMaxHP() const {return MaxHP;}
	const float& GetHP() const {return HP;}
	const float& GetBaseStrength() const {return BaseStrength;}
	const float& GetStrength() const {return Strength;}
	const float& GetBaseDamage() const {return BaseDamage;}
	const float& GetDamage() const {return Damage;}
	const float& GetBaseCriticalChance() const {return BaseCriticalChance;}
	const float& GetCriticalChance() const {return CriticalChance;}
	const float& GetBaseDefense() const {return BaseDefense;}
	const float& GetDefense() const {return Defense;}
	
	/* Attributes Setter */
	void SetBaseMaxHP(const float& Value){BaseMaxHP = Value;}
	void SetMaxHP(const float& Value){MaxHP = Value;}
	void SetHP(const float& Value){HP = Value;}
	void SetBaseStrength(const float& Value){BaseStrength = Value;}
	void SetStrength(const float& Value){Strength = Value;}
	void SetBaseDamage(const float& Value){BaseDamage = Value;}
	void SetDamage(const float& Value){Damage = Value;}
	void SetBaseCriticalChance(const float& Value){BaseCriticalChance = Value;}
	void SetCriticalChance(const float& Value){CriticalChance = Value;}
	void SetBaseDefense(const float& Value){BaseDefense = Value;}
	void SetDefense(const float& Value){Defense = Value;}
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(FDamageInfo DamageInfo);
	void TakeDamage_Internal(FDamageInfo& DamageInfo);
	
	void CalculateDamage(FDamageInfo& DamageInfo);
	bool IsCriticalHit();
	
	// Multicast Func
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnDamageTaken(const FDamageInfo& DamageInfo);
	
protected:
		
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseMaxHP;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHP, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float MaxHP;
	
	UPROPERTY(ReplicatedUsing = OnRep_HP, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float HP;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseStrength;

	UPROPERTY(ReplicatedUsing = OnRep_Strength, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float Strength;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseDamage;

	UPROPERTY(ReplicatedUsing = OnRep_Damage, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float Damage;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseCriticalChance;

	UPROPERTY(ReplicatedUsing = OnRep_CriticalChance, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float CriticalChance;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float BaseDefense;

	UPROPERTY(ReplicatedUsing = OnRep_Defense, EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	float Defense;

public:
	FOnAttributeChanged OnMaxHPChanged;
	FOnAttributeChanged OnHPChanged;
	FOnAttributeChanged OnStrengthChanged;
	FOnAttributeChanged OnDamageChanged;
	FOnAttributeChanged OnCriticalChanceChanged;
	FOnAttributeChanged OnDefenseChanged;
	FOnDamageTaken      OnDamageTaken;
	
};
