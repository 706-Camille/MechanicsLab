// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MLCombatComponent.h"
#include "Ability/MLAbilityBase.h"
#include "NativeGameplayTags.h"
#include "Character/MLCharacterBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UMLCombatComponent::UMLCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	// ...
}	


void UMLCombatComponent::ActivateAbilityByTag(FGameplayTag Tag)
{
	for (UMLAbilityBase* Ability : Abilities)
	{
		if (Ability && Ability->AbilityTag == Tag)
		{
			// 쿨다운, 스태미나 체크 등 추가 가능
			
			Ability->ActivateAbility(ActorInfo, FAbilityDef(Ability->GetClass()));
			break;
		}
	}
}


// Called when the game starts
void UMLCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMLCombatComponent::OnRegister()
{
	Super::OnRegister();
	InitializeDefaultAbilities();
}


void UMLCombatComponent::InitCombatActorInfo(AActor* InOwnerActor, APawn* InAvatarActor, AController* InController)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "InitAbilityActorInfo");

	if (!GetOwner()->HasAuthority()) return;
	
	ActorInfo.OwnerActor = InOwnerActor;
	ActorInfo.AvatarActor = InAvatarActor;
	ActorInfo.CombatComponent = MakeWeakObjectPtr(this);
	ActorInfo.Controller = InController;

	for (UMLAbilityBase* Ability : Abilities)
	{
		if (Ability)
		{
			Ability->ActorInfo = ActorInfo;
		}
	}
	
}

void UMLCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UMLCombatComponent::InitializeDefaultAbilities()
{
	if (!GetOwner()->HasAuthority()) return;
	
	for (TSubclassOf<UMLAbilityBase> AbilityClass : AbilityClasses)
	{
		if (!AbilityClass) continue;

		UMLAbilityBase* Ability = NewObject<UMLAbilityBase>(this, AbilityClass);
		Abilities.Add(Ability);
	}
 
}

bool UMLCombatComponent::TryActivateAbilityByTag(const FGameplayTag& InAbilityTag)
{
	UE_LOG(LogTemp, Warning, TEXT("[TryActivateAbilityByTag] Called on %s (Role: %d, RemoteRole: %d)"), 
	  *GetOwner()->GetName(), (int32)GetOwnerRole(), (int32)GetOwner()->GetRemoteRole());
	
	if (GetOwnerRole() < ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TryActivateAbilityByTag] Client detected, calling Server RPC"));
		ServerTryActivateAbilityByTag(InAbilityTag); // 클라이언트 -> 서버 요청
		return true;
	}
	
	for (UMLAbilityBase* Ability : Abilities)
	{
		if (Ability && Ability->AbilityTag.MatchesTagExact(InAbilityTag))
		{
			
			Ability->ActivateAbility(ActorInfo,FAbilityDef(Ability->GetClass()));
			return true;
		}
	}

	return false;
}

void UMLCombatComponent::ServerTryActivateAbilityByTag_Implementation(const FGameplayTag& InAbilityTag)
{
	ActivateAbilityByTag_Internal(InAbilityTag);
}

bool UMLCombatComponent::ActivateAbilityByTag_Internal(const FGameplayTag& InAbilityTag)
{
	for (UMLAbilityBase* Ability : Abilities)
	{
		if (Ability && Ability->AbilityTag.MatchesTagExact(InAbilityTag))
		{
			Ability->ActivateAbility(ActorInfo, FAbilityDef(Ability->GetClass()));
			return true;
		}
	}
	return false;
}

void UMLCombatComponent::Server_PlayAttackMontage_Implementation(ACharacter* TargetCharacter, UAnimMontage* Montage, const float InPlayRate = 1.0f)
{
	Multicast_PlayAttackMontage(TargetCharacter, Montage, InPlayRate);
}

void UMLCombatComponent::Multicast_PlayAttackMontage_Implementation(ACharacter* TargetCharacter, UAnimMontage* Montage, const float InPlayRate = 1.0f)
{
	if (!Montage || !TargetCharacter) return;
	
	if (UAnimInstance* Anim = TargetCharacter->GetMesh()->GetAnimInstance())
	{
		Anim->Montage_Play(Montage, InPlayRate); // Rate = 1.f
	}
}


// Called every frame
void UMLCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

