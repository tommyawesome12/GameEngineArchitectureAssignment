// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProjectile.h"
#include "FPSPistolComponent.h"
#include "FPSShotgunComponent.h"
#include "FPSCharacter.generated.h"

UCLASS()
class CPPACTORTEST_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Projectile class to spawn
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	//Handles input for moving right and left
	UFUNCTION()
	void MoveRight(float Value);

	//Sets jump flag when key pressed
	UFUNCTION()
	void StartJump();

	//Clears jump flag when key released
	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void SwapToPistol();

	UFUNCTION()
	void SwapToShotgun();

	UFUNCTION()
	void DealDamage();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	//First person mech (arms), visible onlt to owning player
	UPROPERTY(VIsibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	//FUnction that handles firing projectiles
	UFUNCTION()
	void Fire();

	//Gun muzzle offset from the camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(VisibleAnywhere)
	UFPSPistolComponent* PistolComponent;

	UPROPERTY(VisibleAnywhere)
	UFPSShotgunComponent* ShotgunComponent;

	bool UsePistol;

	int Health;
	
};
