// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPistolComponent.h"

// Sets default values for this component's properties
UFPSPistolComponent::UFPSPistolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFPSPistolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFPSPistolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFPSPistolComponent::TraceBeam()
{
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FHitResult HitResult;
	FVector Start = camManager->GetCameraLocation();
	FVector End = Start + camManager->GetCameraRotation().Vector() * 100000.0f;

	FCollisionQueryParams CollQueryParams;

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
			HitActor->DealDamage(2);
		}

	}

}