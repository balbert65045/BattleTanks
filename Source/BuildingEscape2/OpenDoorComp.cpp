// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorComp.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoorComp::UOpenDoorComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorComp::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Owner = GetOwner();
	
}

void UOpenDoorComp::OpenDoor() {
	
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoorComp::CloseDoor() {

	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

float UOpenDoorComp::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (auto* Actor : OverlappingActors) 
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	

	return TotalMass;
}


// Called every frame
void UOpenDoorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GetTotalMassOfActorsOnPlate() > 30.0f) //TODO make the 50 a parameter {
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (LastDoorOpenTime + DoorClosedDelay < GetWorld()->GetTimeSeconds()) {
		CloseDoor();
	}

	//Check if its time to close the door

}

