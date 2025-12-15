// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/EnemyHPWidget.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	RootComponent = CapsuleComponent;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	WidgetHP = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetHP"));
	WidgetHP->SetupAttachment(RootComponent);
	WidgetHP->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetHP->SetRelativeLocation(FVector(0,0,80.f));
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AMannequin::ProcessOnTakeAnyDamage);

	UEnemyHPWidget* HPWidget = Cast<UEnemyHPWidget>(WidgetHP->GetUserWidgetObject());
	if (HPWidget)
	{
		HPWidget->SetOwnerPawn(this);
		OnChangeHP.AddDynamic(HPWidget, &UEnemyHPWidget::ProssesChangeHP);
		HPWidget->ProssesChangeHP(CurrentHP / MaxHP);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RecoverHP();
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHP -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%s HP : %f"), *DamagedActor->GetName(), CurrentHP);

	OnChangeHP.Broadcast(CurrentHP / MaxHP);
	UE_LOG(LogTemp, Warning, TEXT("Broadcast"));
}

void AMannequin::RecoverHP()
{
	if (CurrentHP >= MaxHP)
	{
		return;
	}

	CurrentHP += 0.01f;
}

