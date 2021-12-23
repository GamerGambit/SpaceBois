// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SB_Character.generated.h"

UCLASS()
class SPACEBOIS_API ASB_Character : public ACharacter
{
	GENERATED_BODY()

	/**
	 * Input callback to move forward in local space (or backward if Val is negative).
	 * @param Val Amount of movement in the forward direction (or backward if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category="Pawn")
	virtual void MoveForward(float Val);

	/**
	 * Input callback to strafe right in local space (or left if Val is negative).
	 * @param Val Amount of movement in the right direction (or left if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category="Pawn")
	virtual void MoveRight(float Val);

public:
	/** Name of the SpringArmComponent.  Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName SpringArmComponentName;

	/** Name of the CameraComponent.  Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName CameraComponentName;

protected:
	/** Character spring arm component */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	/** Character camera component */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

public:
	// Sets default values for this character's properties
	ASB_Character(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float StartHealth = 100.0f;

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;

	void Kill();
};
