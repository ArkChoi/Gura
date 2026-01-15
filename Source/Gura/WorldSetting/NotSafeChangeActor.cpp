// Fill out your copyright notice in the Description page of Project Settings.


#include "NotSafeChangeActor.h"
#include "../CPuppet.h"
#include "Components/BoxComponent.h"

// Sets default values
ANotSafeChangeActor::ANotSafeChangeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
}

// Called when the game starts or when spawned
void ANotSafeChangeActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ANotSafeChangeActor::ProcessOnActorBeginOverlap);
}

// Called every frame
void ANotSafeChangeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANotSafeChangeActor::ProcessOnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	ACPuppet* Player = Cast<ACPuppet>(OtherActor);
	if (Player && Player->GetbIsSafe())
	{
		Player->ChangebIsSafe();
	}
}