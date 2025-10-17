// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MLCharacterBase.h"

#include "Component/MLAttributeComponent.h"
#include "Component/MLCombatComponent.h"
#include "Player/MLPlayerState.h"

// Sets default values
AMLCharacterBase::AMLCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	CombatComponent = CreateDefaultSubobject<UMLCombatComponent>("CombatComponent");
	CombatComponent->SetIsReplicated(true);
	
	AttributeComponent = CreateDefaultSubobject<UMLAttributeComponent>("AttributeComponent");
	AttributeComponent->SetIsReplicated(true);
	SetNetUpdateFrequency(100.f);
}

void AMLCharacterBase::InitCombatActorInfo()
{
	AMLPlayerState* MLPlayerState = GetPlayerState<AMLPlayerState>();
	check(MLPlayerState);
	
	
	GetCombatComponent()->InitCombatActorInfo(this, this, MLPlayerState->GetPlayerController());
}

// Called when the game starts or when spawned
void AMLCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMLCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMLCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

