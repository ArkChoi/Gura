// Fill out your copyright notice in the Description page of Project Settings.


#include "CPuppet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACPuppet::ACPuppet()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));
}

// Called when the game starts or when spawned
void ACPuppet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPuppet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPuppet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPuppet::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPuppet::Look);
	}

}

void ACPuppet::Move(const FInputActionValue& Value)
{
	// 2D Vector of movement values returned from the input action
	const FVector2D MovementValue = Value.Get<FVector2D>();

	const FRotator CameraRotation = GetController()->GetControlRotation();
	const FRotator YawRotation = FRotator(0, CameraRotation.Yaw, 0);
	const FRotator YawRollRotation = FRotator(0, CameraRotation.Yaw, CameraRotation.Roll);

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);
	AddMovementInput(ForwardVector, MovementValue.Y);

	//Right ±¸Çö
	const FVector RightVector = UKismetMathLibrary::GetRightVector(YawRollRotation);
	AddMovementInput(RightVector, MovementValue.X);
}

void ACPuppet::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerPitchInput(LookValue.Y);
	AddControllerYawInput(LookValue.X);
}

void ACPuppet::SetCharacterSpeed(float ChangeSpeed)
{
	CharacterSpeed = ChangeSpeed;
	GetCharacterMovement()->MaxWalkSpeed = CharacterSpeed;
}

