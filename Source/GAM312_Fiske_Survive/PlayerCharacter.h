// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GAM312_FISKE_SURVIVE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float axisValue);

	UFUNCTION()
	void MoveRight(float axisValue);
	
	UFUNCTION()
	void LookUp(float axisValue);

	UFUNCTION()
	void Turn(float axisValue);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void Interact();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamComp;

};
