// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "BP_MultiThreadFunctionLib.h"
#include "Async/AsyncWork.h"

/**
 * 
 */
class PrimeCalculationAsyncTask : public FNonAbandonableTask
{
	int32 MaxPrime;

public:
	/*Default constructor*/
	PrimeCalculationAsyncTask(int32 MaxPrime)
	{
		this->MaxPrime = MaxPrime;
	}

	/*This function is needed from the API of the engine. 
	My guess is that it provides necessary information
	about the thread that we occupy and the progress of our task*/
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeCalculationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	/*This function is executed when we tell our task to execute*/
	void DoWork() const
	{
		UBP_MultiThreadFunctionLib::CalculatePrimeNumbers(MaxPrime);
	}
};