// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirtsPersonCamera"));
	check(FPSCameraComponent != nullptr);

	//Attach the camera component to our capsule component
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	//Position camera above eyes
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	//Enable the pawn to control camera rotation
	FPSCameraComponent->bUsePawnControlRotation = true;
	//Create a first person mesh component for owning player
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirtsPersonMesh"));
	check(FPSMesh != nullptr);

	//Only the owning player can see
	FPSMesh->SetOnlyOwnerSee(true);

	//Attach the FPS mesh to the FPS camers
	FPSMesh->SetupAttachment(FPSCameraComponent);

	//Disable some environmental shadows to preserve the illusion of having single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//owning player doesnt see regular body mesh
	GetMesh()->SetOwnerNoSee(true);
	
	//Adds PistolComponent to player character
	PistolComponent = CreateDefaultSubobject<UFPSPistolComponent>(TEXT("PistolComponent"));
	check(PistolComponent != nullptr);
	
	///Adds ShotgunComponent to player character
	ShotgunComponent = CreateDefaultSubobject<UFPSShotgunComponent>(TEXT("ShotgunComponent"));
	check(ShotgunComponent != nullptr);

	UsePistol = true;
	Health = 10;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	//Display a debug message for five seconds
	//The -1 "Key" value argument prevents the message from being updated or refreshed
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter"));
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	PlayerInputComponent->BindAction("SwapToPistol", IE_Pressed, this, &AFPSCharacter::SwapToPistol);
	PlayerInputComponent->BindAction("SwapToShotgun", IE_Pressed, this, &AFPSCharacter::SwapToShotgun);

}

void AFPSCharacter::MoveForward(float Value)
{
	//Find out which way is "forward" and record that the player wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}
void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::SwapToPistol()
{
	ShotgunComponent->SetActive(false);
	PistolComponent->SetActive(true);

	UsePistol = true;
}

void AFPSCharacter::SwapToShotgun()
{
	PistolComponent->SetActive(false);
	ShotgunComponent->SetActive(true);

	UsePistol = false;
}

void AFPSCharacter::Fire()
{
	/*
	//Attempt to fire a Procetile
	if (ProjectileClass)
	{
		//Gets the camera transform
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//Set MUzzleOffset to spawn projectiles slightly in front of camera
		MuzzleOffset.Set(100.0f, 0.0f, 50.0f);

		//TransformMUzzleOffset from camera space to world space
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		//Skew the aim to be slightly upwards
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 0.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			//Spawn the projectile at muzzle
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				//Set the projectile's initial trajectory
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}*/

	if (UsePistol == true) 
	{
		PistolComponent->TraceBeam();
	}
	else 
	{
		ShotgunComponent->TraceBeam();
	}

	
}

void AFPSCharacter::DealDamage()
{
	if (Health > 1)
	{
		Health = Health - 1;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("YouDied"));
	}
	
}

