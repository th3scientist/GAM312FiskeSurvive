// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Resource_Master.generated.h"



UCLASS()
class GAM312_FISKE_SURVIVE_API AResource_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_Master();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FString ResourceName = "Wood";

	UPROPERTY(EditAnywhere)
	int ResourceAmount = 5;

	UPROPERTY(EditAnywhere)
	int TotalResource = 100;

	UPROPERTY()
	FText tempText;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* ResourceNameTxt;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;


};
