// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MLPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Character/MLHeroCharacter.h"
#include "UI/Widget/DamageTextComponent.h"


void AMLPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (AMLHeroCharacter* HeroCharacter = Cast<AMLHeroCharacter>(GetPawn()))
			{
				SubSystem->AddMappingContext(HeroCharacter->GetMappingContext(), 0);
			}
		}
	}
	
}

void AMLPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowDamageNumber"));
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}
