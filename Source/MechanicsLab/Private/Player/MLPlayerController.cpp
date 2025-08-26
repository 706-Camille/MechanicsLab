// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MLPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Character/MLHeroCharacter.h"


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
