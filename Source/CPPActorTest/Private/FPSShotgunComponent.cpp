// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSShotgunComponent.h"

// Sets default values for this component's properties
UFPSShotgunComponent::UFPSShotgunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
}


// Called when the game starts
void UFPSShotgunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFPSShotgunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//Calls line trace event
void UFPSShotgunComponent::TraceBeam()
{
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FHitResult HitResult;

	FVector Start = camManager->GetCameraLocation();
	
	FCollisionQueryParams CollQueryParams;
	//Creates 10 line traces in random directions of the player
	for (int Count = 0; Count < 10; Count++) 
	{
		float RandX = FMath::RandRange(-100.0f, 100.0f);
		float RandY = FMath::RandRange(-100.0f, 100.0f);
		float RandZ = FMath::RandRange(-100.0f, 100.0f);

		AdditionVector.Set(RandX, RandY, RandZ);
		FVector End = Start + camManager->GetCameraRotation().Vector() * 1000.0f + AdditionVector;

		bool bHit = GetWorld()->LineTraceSingleByChannel
		(
			OUT HitResult,
			Start,
			End,
			ECollisionChannel::ECC_Camera,
			CollQueryParams
		);

		if (bHit)
		{
			
			if (AFPSEnemyCharacter* HitActor = Cast<AFPSEnemyCharacter>(HitResult.GetActor()))
			{
				
				HitActor->DealDamage(1);
				
			}

		}
	}
}