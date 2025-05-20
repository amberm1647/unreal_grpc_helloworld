// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorTest.h"
#include "dll/client.h"

// Sets default values
AActorTest::AActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorTest::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, TEXT("Calling get_reply"));
	}

	const char* target_addr = "10.165.125.33:22";
	FString reply = get_reply(target_addr).c_str();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, *reply);
	}
	
}

// Called every frame
void AActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

