// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ChargeAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "kismet/GameplayStatics.h"
#include "../../DamageType/ChargeDamageType.h"
#include "../../CPuppet.h"

FString UAnimNotify_ChargeAttack::GetNotifyName_Implementation() const
{
	return TEXT("ChargeAttack");
}

void UAnimNotify_ChargeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPuppet* Character = Cast<ACPuppet>(MeshComp->GetOwner());
	if (Character)
	{
		APlayerController* PC = Cast<APlayerController>(Character->GetController());
		if (!PC || !PC->HasAuthority())
		{
			return;
		}

		FVector TempVector = Character->GetActorLocation();
		TArray<TEnumAsByte<EObjectTypeQuery>> TempArray;
		TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		TempArray.Add(Pawn);
		TArray<AActor*> IgnoreActor;
		IgnoreActor.Add(Character);
		FHitResult ResultHit;

		UKismetSystemLibrary::SphereTraceSingleForObjects(Character->GetWorld(), TempVector, TempVector, 100.f, TempArray, false, IgnoreActor, EDrawDebugTrace::ForDuration, ResultHit, true);

		if (ResultHit.bBlockingHit)
		{
			UGameplayStatics::ApplyDamage(ResultHit.GetActor(), 20.f, Character->GetController(), Character, UChargeDamageType::StaticClass());
		}

		Character->ReSetbIsAttackCharge();
	}
}
