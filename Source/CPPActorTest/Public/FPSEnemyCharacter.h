// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSEnemyCharacter.generated.h"

class AFPSCharacter;

UCLASS()
class CPPACTORTEST_API AFPSEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSEnemyCharacter();



	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* VisualMesh;

	
	
	//UPROPERTY(VisibleAnywhere);
	//AAIController* 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	int Health=10;

	UFUNCTION()
	void DealDamage(int Damage);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;
};
