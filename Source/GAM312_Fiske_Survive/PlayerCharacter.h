// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_Master.h"
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

	UFUNCTION()
	void FindObject();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Hunger = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float HealthLossFromStarvation = -3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float HungerLossRate = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	float StaminaRegenRate = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Resources")
	int Wood;

	UPROPERTY(EditAnywhere, Category = "Resources")
	int Stone;
	
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Berry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<int> ResourcesArray;

	UPROPERTY(EditAnywhere, Category = "Resources")
	TArray<FString> ResourcesNameArray;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float amount);

	UFUNCTION(BlueprintCallable)
	void SetHunger(float amount);

	UFUNCTION(BlueprintCallable)
	void SetStamina(float amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxStamina(float amount);

	UFUNCTION()
	void DecreaseStats();

	UFUNCTION()
	void GiveResource(float amount, FString resourceType);



};
