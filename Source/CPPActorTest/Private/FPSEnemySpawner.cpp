// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSEnemySpawner.h"

// Sets default values
AFPSEnemySpawner::AFPSEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	
	

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	RootComponent = SpawnBox;

	
}

// Called when the game starts or when spawned
void AFPSEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = SpawnBox->USceneComponent::GetComponentLocation();
	SpawnRotation = GetActorRotation();

	SpawnEnemies();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("SpawnerBeginPlay"));
	
}

// Called every frame
void AFPSEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer = Timer + DeltaTime;
	if (Timer >= 20)
	{
		SpawnEnemies();
		Timer = 0;
	}
}

void AFPSEnemySpawner::SpawnEnemies()
{
	UWorld* World = GetWorld();

	
	
	if (World)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("SpawnerBeginPlay"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//Spawn Enemy at location of spawn point
		AFPSEnemyCharacter* Enemy = World->SpawnActor<AFPSEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);
		//GetWorld()->SpawnActor(EnemyClass, &SpawnLocation);
		if (Enemy)
		{
			Enemy->SpawnDefaultController();
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%p"),Enemy));
	}
	
	
}