// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorComp.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	
}

void UOpenDoorComp::OpenDoor() {
	AActor* Owner = GetOwner();

	FRotator newRotation = FRotator(0.0f, 60.0f, 0.0f);
	Owner->SetActorRotation(newRotation);
}

// Called every frame
void UOpenDoorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}

}

