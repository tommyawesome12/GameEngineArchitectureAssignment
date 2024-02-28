// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		//Use a sphere as a simple collision representation
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		//Set the sphere's collision radius
		CollisionComponent->InitSphereRadius(15.0f);
		//Set the root component to be the collision component
		RootComponent = CollisionComponent;

		if (!ProjectileMovementComponent)
		{
			//use this component to drive this projectiles movement
			ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
			ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
			ProjectileMovementComponent->InitialSpeed = 3000.0f;
			ProjectileMovementComponent->MaxSpeed = 3000.0f;
			ProjectileMovementComponent->bRotationFollowsVelocity = true;
			ProjectileMovementComponent->bShouldBounce = true;
			ProjectileMovementComponent->Bounciness = 0.3f;
			ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
		}

		if (!ProjectileMeshComponent) 
		{
			ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
			static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Sphere.Sphere'"));
			if (Mesh.Succeeded())
			{
				ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
			}

			static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Fbx_Default_Material.Fbx_Default_Material'"));
			if (Material.Succeeded())
			{
				ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
			}
			ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
			ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
			ProjectileMeshComponent->SetupAttachment(RootComponent);

			//Delete projectile after 3 seconds
			InitialLifeSpan = 3.0f;

			//Sets spphere collision name to projectile
			CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

			//EventCalled when component hits something
			CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);

		}
	}
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Function that initialises the projectiles velocity in the shoot direction
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HitResult"));
		
	}

}

