// Fill out your copyright notice in the Description page of Project Settings.


#include "CPuppet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "Enemy/Mannequin.h"


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

	SetCharacterSpeed(CharacterSpeed);
}

// Called when the game starts or when spawned
void ACPuppet::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &ACPuppet::ProcessOnTakeAnyDamage);
}

// Called every frame
void ACPuppet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDash)
	{
		AddActorLocalOffset(FVector(4.5f, 0, 0));
	}
	if (bIsLockOn)
	{
		if (LockEnemy)
		{
			FVector ThisLocation = GetActorLocation();
			FVector LockEnemyLocation = LockEnemy->GetActorLocation();

			GetController()->SetControlRotation(UKismetMathLibrary::FindLookAtRotation(ThisLocation, LockEnemyLocation));
		}
	}
}

// Called to bind functionality to input
void ACPuppet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPuppet::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPuppet::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACPuppet::Attack);

		EnhancedInputComponent->BindAction(PowerAttackAction, ETriggerEvent::Started, this, &ACPuppet::Charged);
		EnhancedInputComponent->BindAction(PowerAttackAction, ETriggerEvent::Completed, this, &ACPuppet::PowerAttack);

		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ACPuppet::DoRun);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &ACPuppet::ResetWalk);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Canceled, this, &ACPuppet::Dash);

		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Triggered, this, &ACPuppet::DoGuard);
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Completed, this, &ACPuppet::UnDoGuard);
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Canceled, this, &ACPuppet::PerfectGuard);

		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Triggered, this, &ACPuppet::OnLockOn);
	}

}

void ACPuppet::Move(const FInputActionValue& Value)
{
	if (!GetCanPlayAnimMontage())
	{
		if (!bIsGuard)
		{
			return;
		}
	}

	
	// 2D Vector of movement values returned from the input action
	const FVector2D MovementValue = Value.Get<FVector2D>();

	const FRotator CameraRotation = GetController()->GetControlRotation();
	const FRotator YawRotation = FRotator(0, CameraRotation.Yaw, 0);
	const FRotator YawRollRotation = FRotator(0, CameraRotation.Yaw, CameraRotation.Roll);

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);
	AddMovementInput(ForwardVector, MovementValue.Y);

	//Right 구현
	const FVector RightVector = UKismetMathLibrary::GetRightVector(YawRollRotation);
	AddMovementInput(RightVector, MovementValue.X);
}

void ACPuppet::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerPitchInput(LookValue.Y);
	AddControllerYawInput(LookValue.X);

}

void ACPuppet::Attack(const FInputActionValue& Value)
{

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance();
;
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(AttackMontage))
		{
			if (GetCanPlayAnimMontage())
			{
				PlayComboMontage(ComboCount);
			}
		}
		else
		{
			bIsComboAttack = true;
		}
	}
}

void ACPuppet::PlayComboMontage(int32 InComboCount)
{
	if (ComboCount > 3)
	{
		ReSetComboCount();
		ReSetbIsComboAttack();
		ReSetbIsAttack();
		return;
	}

	bIsAttack = true;
	FString SectionName = FString::Printf(TEXT("%d"), InComboCount);
	PlayAnimMontage(AttackMontage, 1.0f, FName(*SectionName));
	ReSetbIsComboAttack();
	ComboCount++;
}

void ACPuppet::PowerAttack()
{
	float NowTime = UGameplayStatics::GetTimeSeconds(this);
	PowerChargingTime = NowTime - PowerChargingTime;

	if (PowerChargingTime >= 1.5f)
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerChargeAttack"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerAttack"));
	}
}

void ACPuppet::Charged(const FInputActionValue& Value)
{
	PowerChargingTime = UGameplayStatics::GetTimeSeconds(this);
}

void ACPuppet::DoRun()
{
	if (!GetCanPlayAnimMontage())
	{
		return;
	}

	SetCharacterSpeed(600.f);
}

void ACPuppet::ResetWalk()
{
	if (!GetCanPlayAnimMontage())
	{
		return;
	}

	SetCharacterSpeed(300.f);
}

void ACPuppet::Dash()
{
	if (!GetCanPlayAnimMontage())
	{
		return;
	}

	bIsDash = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayAnimMontage(DashMontage,2.5f);

	//카메라 쭉 늘어나서 천천히 따라가는 코드 추가 필요
}

void ACPuppet::PerfectGuard()
{
	if (!GetCanPlayAnimMontage())
	{
		return;
	}

	if (!PerfectGuardMontage || GetMesh()->GetAnimInstance()->Montage_IsPlaying(PerfectGuardMontage))
	{
		return;
	}

	PlayAnimMontage(PerfectGuardMontage);

	FVector TempVector = GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> TempArray;
	TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	TempArray.Add(Pawn);
	TArray<AActor*> IgnoreActor;
	IgnoreActor.Add(this);
	FHitResult ResultHit;

	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TempVector, TempVector, 100.f, TempArray, false, IgnoreActor, EDrawDebugTrace::ForDuration, ResultHit, true);

	AMannequin* Enemy = Cast<AMannequin>(ResultHit.GetActor());
	if (Enemy)
	{
		bIsPerfectGuard = true;
	}

}

void ACPuppet::DoGuard()
{
	if (bIsGuard)
	{
		return;
	}

	bIsGuard = true;
	
	SetCharacterSpeed(100.f);
}

void ACPuppet::UnDoGuard()
{
	UE_LOG(LogTemp, Warning, TEXT("UnDoGuard"));
	//약 1.5 초 정도 뒤에
	bIsGuard = false;
	ResetWalk();
}

void ACPuppet::OnLockOn()
{
	if (bIsLockOn)
	{
		ReSetbIsLockOn();
		LockEnemy = nullptr;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("LockOn"));

	FVector StartVector = Camera->GetComponentTransform().GetTranslation();
	FVector EndVector = StartVector + ((Camera->GetComponentTransform().GetRotation().GetForwardVector()) * 1000.f);
	TArray<TEnumAsByte<EObjectTypeQuery>> TempArray;
	TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	TempArray.Add(Pawn);
	TArray<AActor*> IgnoreActor;
	IgnoreActor.Add(this);
	FHitResult ResultHit;

	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartVector, EndVector, 100.f, TempArray, false, IgnoreActor, EDrawDebugTrace::ForDuration, ResultHit, true);

	AMannequin* Enemy = Cast<AMannequin>(ResultHit.GetActor());
	if (Enemy)
	{
		LockEnemy = Enemy;
		bIsLockOn = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		//전방 보기
		FRotator MeshForwardRotator = GetMesh()->GetForwardVector().Rotation();
		MeshForwardRotator.Yaw += 90.f;
		GetController()->SetControlRotation(MeshForwardRotator);
	}
}

void ACPuppet::SetCharacterSpeed(float ChangeSpeed)
{
	CharacterSpeed = ChangeSpeed;
	GetCharacterMovement()->MaxWalkSpeed = CharacterSpeed;
}

void ACPuppet::ReSetComboCount()
{
	ComboCount = 1;
}

void ACPuppet::ReSetbIsComboAttack()
{
	bIsComboAttack = false;
}

void ACPuppet::EndDash()
{
	bIsDash = false;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACPuppet::EndImpulse()
{
	GetCapsuleComponent()->SetSimulatePhysics(false);
	bIsImpulse = false;
}

void ACPuppet::ReSetStatus()
{
	EndDash();
	EndImpulse();
	ReSetComboCount();
}

bool ACPuppet::GetCanPlayAnimMontage()
{
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance();
		;
		if (AnimInstance && AnimInstance->Montage_IsPlaying(DashMontage))
		{
			return false;
		}
		else if (AnimInstance && AnimInstance->Montage_IsPlaying(HitMontage))
		{
			return false;
		}
		else if (bIsAttack)
		{
			return false;
		}
		else if (bIsGuard)
		{
			return false;
		}
		else if (bIsPerfectGuard)
		{
			return false;
		}
	}

	ReSetStatus();
	return true;
}

void ACPuppet::PlayHitAnimMontage()
{
	if (HitMontage)
	{
		PlayAnimMontage(HitMontage);
	}
}

void ACPuppet::ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsGuard)
	{
		float GuardDamage = Damage / 2; //일단 2는 50% 뎀감 무기 하드코딩 해둔 것 나중에 무기 만들면 바꿀것
		CurrentHP -= GuardDamage;
		UE_LOG(LogTemp, Warning, TEXT("%s HP : %f"), *DamagedActor->GetName(), CurrentHP);

		return;
	}
	else if (bIsPerfectGuard)
	{
		//이펙트 하나 띄어주고..
		UE_LOG(LogTemp, Warning, TEXT("PerfectGuard"));
		return;
	}

	if (!GetCanPlayAnimMontage())
	{
		return;
	}

	CurrentHP -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%s HP : %f"), *DamagedActor->GetName(), CurrentHP);

	ACharacter* Enemy = Cast<ACharacter>(DamageCauser);
	if (Enemy)
	{
		FVector EnemyLocation = Enemy->GetMesh()->GetComponentLocation();
		FVector MyLocation = GetMesh()->GetComponentLocation();
		FVector ImpulseForce = (MyLocation - EnemyLocation).GetSafeNormal();
		ImpulseForce.Z = 0;
		ImpulseForce *= 5000;

		UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), ImpulseForce.X, ImpulseForce.Y, ImpulseForce.Z);

		bIsImpulse = true;
		GetCapsuleComponent()->SetSimulatePhysics(true);
		GetCapsuleComponent()->AddImpulse(ImpulseForce);
	}

	PlayHitAnimMontage();
}
