// Fill out your copyright notice in the Description page of Project Settings.


#include "PunchMachine.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Widget/PowerScoreWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
APunchMachine::APunchMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);
	Body->SetSimulatePhysics(true);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(RootComponent);
	PhysicsConstraint->ComponentName1.ComponentName = TEXT("Body");
	PhysicsConstraint->ComponentName2.ComponentName = TEXT("Plane");

	WidgetScore = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetScore"));
	WidgetScore->SetupAttachment(RootComponent);
	WidgetScore->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetScore->SetRelativeLocation(FVector(0, 0, 110.f));
}

// Called when the game starts or when spawned
void APunchMachine::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &APunchMachine::ProcessOnTakeAnyDamage);

	if (WidgetScore)
	{
		UPowerScoreWidget* ScoreWidget = Cast<UPowerScoreWidget>(WidgetScore->GetUserWidgetObject());
		if (ScoreWidget)
		{
			ScoreWidget->SetOwner(this);
			ScoreOutput.AddDynamic(ScoreWidget, &UPowerScoreWidget::ProssesScoreOutput);
			ScoreWidget->ProssesScoreOutput(0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetScore Not Found"));
	}
}

// Called every frame
void APunchMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APunchMachine::ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	ACharacter* Enemy = Cast<ACharacter>(DamageCauser);
	if (Enemy)
	{
		FVector EnemyLocation = Enemy->GetMesh()->GetComponentLocation();
		FVector MyLocation = Body->GetComponentLocation();
		ImpulseForce = (MyLocation - EnemyLocation).GetSafeNormal();
		ImpulseForce.Z = 0;
		PowerCharge = Damage;
		if (PowerCharge >= 70)
		{
			ImpulseForce *= 100000.f;
		}
		else if (PowerCharge >= 40)
		{
			ImpulseForce *= 10000.f;
		}
		else
		{
			ImpulseForce *= 1000.f;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Server : %f %f %f"), ImpulseForce.X, ImpulseForce.Y, ImpulseForce.Z);
		if (PowerCharge > HighScore)
		{
			HighScore = PowerCharge;
		}
	}

	S2A_PlayImpulse();
}

void APunchMachine::S2A_PlayImpulse_Implementation()
{

	UE_LOG(LogTemp, Warning, TEXT("PowerCharge : %d"), PowerCharge);
	Body->AddImpulse(ImpulseForce);

	//일단 하드 코딩
	ScoreOutput.Broadcast(PowerCharge);

	HighScoreChange.Broadcast(HighScore);
}

void APunchMachine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APunchMachine, ImpulseForce);
	DOREPLIFETIME(APunchMachine, PowerCharge);
	DOREPLIFETIME(APunchMachine, HighScore);

}
