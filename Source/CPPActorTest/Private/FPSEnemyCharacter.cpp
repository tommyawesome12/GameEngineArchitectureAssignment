// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSEnemyCharacter.h"
#include "FPSCharacter.h"

// Sets default values
AFPSEnemyCharacter::AFPSEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(75.0f);
		CollisionComponent->SetupAttachment(RootComponent);
		CollisionComponent->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AFPSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSEnemyCharacter::BeginOverlap);
	
}

// Called every frame
void AFPSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AFPSEnemyCharacter::DealDamage(int Damage) 
{
	Health = Health - Damage; 
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(Health));
	if (Health <= 0)
	{
		Destroy();
	}
}

void AFPSEnemyCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	if (AFPSCharacter* HitActor = Cast<AFPSCharacter>(OtherActor))
	{
		
		HitActor->DealDamage();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::FromInt(HitActor->Health));
	}
}


