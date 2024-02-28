// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorFactories/ActorFactoryEmptyActor.h"
#include "FPSEnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "FPSEnemySpawner.generated.h"

UCLASS()
class CPPACTORTEST_API AFPSEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnEnemies();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AFPSEnemyCharacter> EnemyClass;

	FVector SpawnLocation;

	FRotator SpawnRotation;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	float Timer=0;
};

