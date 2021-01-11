// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiThreadTest/BP_MultiThreadFunctionLib.h"
// #include<iostream>
// #include<map>
//
// using namespace std;
// struct CacheNode {
// 	int key;
// 	int value;
// 	CacheNode *pre, *next;
// 	CacheNode(int k, int v) : key(k), value(v), pre(NULL), next(NULL) {}
// };

void UBP_MultiThreadFunctionLib::CalculatePrimeNumbers(int32 UpperLimit)
{
	//Calculating the prime numbers...
	for (int32 i = 1; i <= UpperLimit; i++)
	{
		bool isPrime = true;
		for (int32 j = 2; j <= i / 2; j++)
		{
			if (FMath::Fmod(i, j) == 0)
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime) 
			GLog->Log("Prime number #" + FString::FromInt(i) + ": " + FString::FromInt(i));
	}
}


