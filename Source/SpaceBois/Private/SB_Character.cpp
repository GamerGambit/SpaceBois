// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_Character.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>
#include "Engine/SkeletalMesh.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

FName ASB_Character::SpringArmComponentName(TEXT("SpringArmComponent0"));
FName ASB_Character::CameraComponentName(TEXT("CameraComponent0"));

// Sets default values
ASB_Character::ASB_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	Health = StartHealth;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> MannequinMesh;
		ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimInstance;
		FConstructorStatics()
			: MannequinMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"))
			, AnimInstance(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP"))
		{}
	};

	static FConstructorStatics ConstructorStatics;

	GetMesh()->SetSkeletalMesh(ConstructorStatics.MannequinMesh.Object);
	GetMesh()->SetAnimInstanceClass(ConstructorStatics.AnimInstance.Object->GeneratedClass);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -95), FRotator(0, 270, 0));
	GetMesh()->SetIsReplicated(true);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(ASB_Character::SpringArmComponentName);
	SpringArmComponent->SetRelativeLocation(FVector(0, 0, 8.5));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(ASB_Character::CameraComponentName);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
float ASB_Character::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float dmg = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Health -= dmg;

	if (Health <= 0.0f)
	{
		Kill();
	}

	return dmg;
}

void ASB_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASB_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASB_Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASB_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASB_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASB_Character::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ASB_Character::StopJumping);
}

void ASB_Character::Kill()
{
	// Only the server can kill us
	if (GetNetMode() == NM_Client)
		return;

	if (Controller != nullptr)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASB_Character::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASB_Character, Health);
}

void ASB_Character::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
		}
	}
}

void ASB_Character::MoveForward(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
		}
	}
}
