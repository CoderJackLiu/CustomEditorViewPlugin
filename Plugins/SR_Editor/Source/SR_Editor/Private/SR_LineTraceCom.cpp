// Fill out your copyright notice in the Description page of Project Settings.


#include "SR_LineTraceCom.h"


#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
USR_LineTraceCom::USR_LineTraceCom()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bTickInEditor=true;
	
	// ...
}


// Called when the game starts
void USR_LineTraceCom::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USR_LineTraceCom::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SendLineTrace();
	// ...
}

void USR_LineTraceCom::SendLineTrace_Implementation()
{
	//射线检测实例
	UWorld *world = GetWorld();
	if (world)
	{
		FHitResult hitResult;
		const TArray<AActor*> ignoreActors;
		// FVector end = GetActorForwardVector() * SingleTraceLineLength + GetActorLocation();
		FVector end = FVector(1,0,0)*1000.f;
		
		//参数说明， 射线需要两个点，一个开始一个结束点。同蓝图使用一样
		const bool isHit = UKismetSystemLibrary::LineTraceSingle(world, FVector(0), end, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ignoreActors, EDrawDebugTrace::ForDuration, hitResult, true);

		if (isHit)
		{
			AActor *hitActor = hitResult.GetActor();
			if (hitActor)
			{
				// AHitTarget *target = Cast<AHitTarget>(hitActor);
				// if (target)
				// {
				// 	//调用射线碰撞到的物体函数
				// 	target->OnRaycastHit();
				// }
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, TEXT(" hiting actor!"));
			}
		}
	}
}

