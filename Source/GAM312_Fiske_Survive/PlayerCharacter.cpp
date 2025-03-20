// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));

	PlayerCamComp->SetupAttachment(GetMesh(), "head");
	PlayerCamComp->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerCharacter::DecreaseStats, 2.0f, true);
	ResourcesArray = { 0, 0, 0 };
	ResourcesNameArray = { "Wood", "Stone", "Berry" };
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerCharacter::StopJump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::MoveForward(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void APlayerCharacter::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

void APlayerCharacter::LookUp(float axisValue)
{
}

void APlayerCharacter::Turn(float axisValue)
{
}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::Interact()
{
	FindObject();
}

void APlayerCharacter::FindObject()
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCamComp->GetComponentLocation();
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f;
	FVector EndLocation = StartLocation + Direction;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	// perform the line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		// check that the hit object is a resource object
		AResource_Master* HitResource = Cast<AResource_Master>(HitResult.GetActor());

		// stamina check
		if (Stamina > -StaminaLossOnResourceCollect)
		{
			// is valid
			if (HitResource)
			{
				FString hitName = HitResource->ResourceName;
				int resourceValue = HitResource->ResourceAmount;
				SetStamina(StaminaLossOnResourceCollect);
				
				if (HitResource->TotalResource >= resourceValue)
				{
					GiveResource(resourceValue, hitName);
					// Subtract from total resource
					HitResource->TotalResource = HitResource->TotalResource - resourceValue;

					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected"));

					UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal,
						FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);

				}
				// Gives the resources leftover when resourceValue is not a multiple of the total
				else if (HitResource->TotalResource > 0.0f)
				{
					GiveResource(HitResource->TotalResource, hitName);
					HitResource->Destroy();

					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
				}
				// Destroys resource for the case when resourceValue is a multiple of the total
				if (HitResource->TotalResource == 0.0f)
				{
					HitResource->Destroy();

					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
				}
			}
		}
	}
}

void APlayerCharacter::SetHealth(float amount)
{
	if (Health + amount < MaxHealth)
	{
		Health = amount + Health;
	}
	else if (Health + amount >= MaxHealth)
	{
		Health = MaxHealth;
	}
}

void APlayerCharacter::SetHunger(float amount)
{
	if (Hunger + amount < 100)
	{
		Hunger = amount + Hunger;
	}
	else if (Hunger + amount >= 100)
	{
		Hunger = 100;
	}
}

void APlayerCharacter::SetStamina(float amount)
{
	if (Stamina + amount < MaxStamina)
	{
		Stamina = amount + Stamina;
	}
	else if (Stamina + amount >= MaxStamina)
	{
		Stamina = MaxStamina;
	}
}

void APlayerCharacter::SetMaxHealth(float amount)
{
	MaxHealth = amount;
}

void APlayerCharacter::SetMaxStamina(float amount)
{
	MaxStamina = amount;
}

void APlayerCharacter::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(HungerLossRate);
		SetStamina(StaminaRegenRate);
	}
	
	if (Hunger <= 0)
	{
		SetHealth(HealthLossFromStarvation);
	}
}

void APlayerCharacter::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;
	}

	if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount;
	}

	if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount;
	}
}

