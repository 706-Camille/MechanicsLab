// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MLAttributeComponent.h"

#include "Character/MLHeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/MLPlayerController.h"


// Sets default values for this component's properties
UMLAttributeComponent::UMLAttributeComponent()
{
	SetIsReplicatedByDefault(true);
}

void UMLAttributeComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, MaxHP);
	DOREPLIFETIME(ThisClass, HP);
	DOREPLIFETIME(ThisClass, Strength);
}


void UMLAttributeComponent::OnRep_MaxHP()
{
	OnMaxHPChanged.Broadcast(GetMaxHP());
}

void UMLAttributeComponent::OnRep_HP()
{
	OnHPChanged.Broadcast(GetHP());
}

void UMLAttributeComponent::OnRep_Strength()
{
	OnStrengthChanged.Broadcast(GetStrength());
}

void UMLAttributeComponent::OnRep_Damage()
{
}

void UMLAttributeComponent::OnRep_Defense()
{
}

void UMLAttributeComponent::OnRep_CriticalChance()
{
}

void UMLAttributeComponent::TakeDamage(FDamageInfo DamageInfo)
{
	TakeDamage_Internal(DamageInfo);
}

void UMLAttributeComponent::TakeDamage_Internal(FDamageInfo& DamageInfo)
{
	
	UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Enter Owner=%s HasAuthority=%d HP=%.2f Instigator=%s (class=%s)"),
		*GetNameSafe(GetOwner()),
		GetOwner() ? (int32)GetOwner()->HasAuthority() : -1,
		HP,
		*GetNameSafe(DamageInfo.Instigator),
		DamageInfo.Instigator ? *DamageInfo.Instigator->GetClass()->GetName() : TEXT("null"));

	if (!GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Return: no authority (client)."));
		return;
	}

	if (HP <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Return: already dead. HP=%.2f"), HP);
		return;
	}

	CalculateDamage(DamageInfo);

	if (DamageInfo.FinalDamage <= 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Return: FinalDamage <= 0. FinalDamage=%.2f"), DamageInfo.FinalDamage);
		return;
	}

	HP = FMath::Clamp(HP - DamageInfo.FinalDamage, 0.f, MaxHP);

	AMLHeroCharacter* SourceCharacter = Cast<AMLHeroCharacter>(DamageInfo.Instigator);
	if (!SourceCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Return: Instigator is NOT AMLHeroCharacter. Instigator=%s (class=%s)"),
			*GetNameSafe(DamageInfo.Instigator),
			DamageInfo.Instigator ? *DamageInfo.Instigator->GetClass()->GetName() : TEXT("null"));
		return;
	}

	// GetPlayerController(0)는 멀티/서버에서 위험함 -> 실제 소유 컨트롤러 사용
	AMLPlayerController* PC = Cast<AMLPlayerController>(SourceCharacter->GetController());
	UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Resolved PC=%s Controller=%s"),
		*GetNameSafe(PC),
		*GetNameSafe(SourceCharacter->GetController()));

	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Failed to get AMLPlayerController. Cannot show damage number."));
		return;
	}

	// 주의: 여기 호출은 서버에서 실행 중임. ShowDamageNumber가 클라 UI면 Client RPC가 필요할 수 있음.
	UE_LOG(LogTemp, Warning, TEXT("[TakeDamage_Internal] Calling ShowDamageNumber Damage=%.2f Target=%s"),
		DamageInfo.FinalDamage, *GetNameSafe(GetOwner()));

	PC->ShowDamageNumber(DamageInfo.FinalDamage, Cast<ACharacter>(GetOwner()));
	
}


void UMLAttributeComponent::CalculateDamage(FDamageInfo& DamageInfo)
{
	checkf(DamageInfo.Instigator, TEXT("DamageInfo.Instigator In UMLAttributeComponent::CalculateDamage is Null"));
	
	UMLAttributeComponent* InstigatorAC = DamageInfo.Instigator->FindComponentByClass<UMLAttributeComponent>();
	
	// TODO
	if (!InstigatorAC)
	{
		return;
	}
	
	
	DamageInfo.bIsCritical = InstigatorAC->IsCriticalHit();
	
	const float InstigatorDamage = InstigatorAC->GetDamage();
	const float MinDamage = 0.9f * InstigatorDamage;
	const float MaxDamage = 1.2f * InstigatorDamage;
	const float RandomDamage = FMath::RandRange(MinDamage, MaxDamage);
	float FinalCalculatedDamage = RandomDamage * DamageInfo.DamageScale;
	
	if (DamageInfo.bIsCritical)
	{
		const float CriticalMultiplier = 2.f;
		FinalCalculatedDamage *= CriticalMultiplier;
	}
	
	DamageInfo.FinalDamage = FinalCalculatedDamage;
}

bool UMLAttributeComponent::IsCriticalHit()
{
	const float RandomValue = FMath::RandRange(0.0f, 1.0f);
	
	return RandomValue < GetCriticalChance();
}

void UMLAttributeComponent::MulticastOnDamageTaken_Implementation(const FDamageInfo& DamageInfo)
{
	OnDamageTaken.Broadcast(DamageInfo);
}

