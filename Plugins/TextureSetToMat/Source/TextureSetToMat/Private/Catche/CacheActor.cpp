// Fill out your copyright notice in the Description page of Project Settings.


#include "Catche/CacheActor.h"
#include<iostream>
#include<map>

using namespace std;

// struct CacheNode {
// 	int key;      // 键
// 	int value;    // 值
// 	CacheNode *pre, *next;  // 节点的前驱、后继指针
// 	CacheNode(int k, int v) : key(k), value(v), pre(NULL), next(NULL) {}
// };

// Sets default values
ACacheActor::ACacheActor():TokenCache(1000)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ACacheActor::BeginPlay()
{
	Super::BeginPlay();
	// TokenCache=1;
}

// Called every frame
void ACacheActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void ACacheActor::InitTokenTocache()
{
	const FString TokenKey="UModleToken";

	TokenCache.Add(TokenKey,"AAASCCC");
	TokenCache.FindAndTouchChecked(TokenKey);
	// TokenCache.FindAndTouchChecked(TokenKey);
	
}

void ACacheActor::SetTokenTocache(FString TokenValue)
{
	const FString TokenKey="UModleToken";
	TokenCache.Add(TokenKey,TokenValue);
}

FString ACacheActor::ReadToken(FString KeyStr)
{
	const FString TokenKey="UModleToken";
	if (TokenCache.FindAndTouch(TokenKey))
	{
		FString TokenStr=*TokenCache.FindAndTouchChecked(TokenKey);
		return TokenStr;
	}
	return "";
}

