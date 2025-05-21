// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorTest.h"
#include "dll/client.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"


// Sets default values
AActorTest::AActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
	}
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

	FVector ActorLoc = GetTransform().GetLocation();
	FTransform TextTransform;
	TextTransform.SetLocation(FVector(ActorLoc.X + 70, ActorLoc.Y, ActorLoc.Z + 40));

	NewText = Cast<UTextRenderComponent>(AddComponentByClass(UTextRenderComponent::StaticClass(), true, TextTransform, false));
	NewText->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	NewText->SetTextRenderColor(FColor::Red);
	NewText->SetText(FText::FromString(*reply));
	NewText->SetRelativeScale3D(FVector(3, 3, 3));
	NewText->bHiddenInGame = false;
}

// Called every frame
void AActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

