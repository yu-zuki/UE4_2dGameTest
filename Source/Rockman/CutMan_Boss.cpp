// Fill out your copyright notice in the Description page of Project Settings.


#include "CutMan_Boss.h"

// Sets default values
ACutMan_Boss::ACutMan_Boss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACutMan_Boss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACutMan_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACutMan_Boss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

