// Fill out your copyright notice in the Description page of Project Settings.


#include "SR_LineTraceActor.h"

#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ASR_LineTraceActor::ASR_LineTraceActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScen=CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent=DefaultScen;
	

	SplineCom=CreateDefaultSubobject<USplineComponent>(TEXT("SplineCom"));
	SplineCom->SetupAttachment(DefaultScen);

	LineTraceCom=CreateDefaultSubobject<USR_LineTraceCom>(TEXT("LineTraceCom"));

}

// Called when the game starts or when spawned
void ASR_LineTraceActor::BeginPlay()
{
	Super::BeginPlay();
	UWorld *world = GetWorld();

	FHitResult hitResult;
	const TArray<AActor*> ignoreActors;
	// FVector end = GetActorForwardVector() * SingleTraceLineLength + GetActorLocation();
	// FVector end = FVector(1,0,0)*1000.f;
	FVector end=FVector(0);
	//参数说明， 射线需要两个点，一个开始一个结束点。同蓝图使用一样
	bool isHit = UKismetSystemLibrary::LineTraceSingle(world, FVector(0), end, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ignoreActors, EDrawDebugTrace::ForDuration, hitResult, true);

}

// Called every frame
void ASR_LineTraceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

