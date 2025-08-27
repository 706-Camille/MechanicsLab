// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MLHeroCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AMLHeroCharacter::AMLHeroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 회전이 컨트롤러(마우스) 회전을 따라가지 않게
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// 캐릭터가 움직이는 방향으로 자연스럽게 회전
	GetCharacterMovement()->bOrientRotationToMovement = false; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f); // 회전 속도 조절
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f; 
	SpringArm->bUsePawnControlRotation = true; // 스프링암은 컨트롤러 회전을 따라간다

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // 카메라는 스프링암을 따라가기만 하면 되므로 false 입니다.
}

void AMLHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AMLHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMLHeroCharacter::Move);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMLHeroCharacter::Look);
		}

		if (ZoomAction)
		{
			EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AMLHeroCharacter::Zoom);
		}

		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMLHeroCharacter::StartSprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMLHeroCharacter::EndSprint);
		}
	}
	
}	

void AMLHeroCharacter::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "oo");
	if (Controller)
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "Movement");
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void AMLHeroCharacter::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMLHeroCharacter::Zoom(const FInputActionValue& InputActionValue) 
{
	const FVector ZoomAxisValue = InputActionValue.Get<FVector>();

	if (SpringArm)
	{
		float NewArmLength = SpringArm->TargetArmLength - (ZoomAxisValue.X * ZoomSpeed);

		SpringArm->TargetArmLength = FMath::Clamp(NewArmLength, MinZoomLength, MaxZoomLength);
	}
	
}
void AMLHeroCharacter::StartSprint(const FInputActionValue& InputActionValue) 
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMLHeroCharacter::EndSprint(const FInputActionValue& InputActionValue) 
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

