// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::SetBarrelRefference(UStaticMeshComponent* BarrelToSet) {
	Barrel = BarrelToSet;
	//	UE_LOG(LogTemp, Warning, TEXT("Barrel is set"));
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)const
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace)
		)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *TankName,*AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const {
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;



	//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimAsRotator.ToString());
}



