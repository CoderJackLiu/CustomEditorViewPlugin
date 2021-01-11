// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiThreadTest/MultiThread_Actor.h"

#include "MultiThreadTest/BP_MultiThreadFunctionLib.h"
#include "MultiThreadTest/PrimeCalculationAsyncTask.h"


// Sets default values
AMultiThread_Actor::AMultiThread_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMultiThread_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMultiThread_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMultiThread_Actor::CalculatePrimeNumbers(int32 UpperLimit)
{
	UBP_MultiThreadFunctionLib::CalculatePrimeNumbers(50000);
}

void AMultiThread_Actor::CalculatePrimeNumbersAsync()
{
	auto task = new FAutoDeleteAsyncTask<PrimeCalculationAsyncTask>(MaxPrime);
	if (task)
		task -> StartBackgroundTask();
	
}

