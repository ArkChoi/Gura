// Fill out your copyright notice in the Description page of Project Settings.


#include "PunchMachine.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
APunchMachine::APunchMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APunchMachine::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &APunchMachine::ProcessOnTakeAnyDamage);

}

// Called every frame
void APunchMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APunchMachine::ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	/*ACharacter* Enemy = Cast<ACharacter>(DamageCauser);
	if (Enemy)
	{
		FVector EnemyLocation = Enemy->GetMesh()->GetComponentLocation();
		FVector MyLocation = GetMesh()->GetComponentLocation();
		FVector ImpulseForce = (MyLocation - EnemyLocation).GetSafeNormal();
		ImpulseForce.Z = 0;
		ImpulseForce *= ImpulseForceAdder;

		UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), ImpulseForce.X, ImpulseForce.Y, ImpulseForce.Z);

		GetMesh()->AddImpulse(ImpulseForce, true);
	}*/
}
