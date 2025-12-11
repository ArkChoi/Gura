// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SmollAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../CPuppet.h"
#include "kismet/GameplayStatics.h"
#include "../../DamageType/StrikeDamageType.h"

FString UAnimNotify_SmollAttack::GetNotifyName_Implementation() const
{
	return TEXT("SmollAttack");
}

void UAnimNotify_SmollAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPuppet* Character = Cast<ACPuppet>(MeshComp->GetOwner());
	if (Character)
	{
		FString TempString = TEXT("hand_r");

		FVector RightHand = Character->GetMesh()->GetBoneLinearVelocity(FName(*TempString));


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
			UGameplayStatics::ApplyDamage(ResultHit.GetActor(), 10.f, Character->GetController(), Character, UStrikeDamageType::StaticClass());

			UE_LOG(LogTemp, Warning, TEXT("%s"), *ResultHit.GetActor()->GetName());
		}
	}
}
