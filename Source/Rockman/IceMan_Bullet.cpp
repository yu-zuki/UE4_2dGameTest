// Fill out your copyright notice in the Description page of Project Settings.


#include "IceMan_Bullet.h"

// Sets default values
AIceMan_Bullet::AIceMan_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIceMan_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIceMan_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

