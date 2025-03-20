// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_Master.h"

// Sets default values
AResource_Master::AResource_Master()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ResourceNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	ResourceNameTxt->SetupAttachment(Mesh);
	


}

// Called when the game starts or when spawned
void AResource_Master::BeginPlay()
{
	Super::BeginPlay();
	
	tempText = tempText.FromString(ResourceName);
	ResourceNameTxt->SetText(tempText);

}

// Called every frame
void AResource_Master::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

