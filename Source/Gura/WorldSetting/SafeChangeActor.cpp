// Fill out your copyright notice in the Description page of Project Settings.


#include "SafeChangeActor.h"
#include "../CPuppet.h"
#include "Components/BoxComponent.h"

// Sets default values
ASafeChangeActor::ASafeChangeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
}

// Called when the game starts or when spawned
void ASafeChangeActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ASafeChangeActor::ProcessOnActorBeginOverlap);
}

// Called every frame
void ASafeChangeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASafeChangeActor::ProcessOnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	ACPuppet* Player = Cast<ACPuppet>(OtherActor);
	if (Player && !Player->GetbIsSafe())
	{
		Player->ChangebIsSafe();
	}
}

