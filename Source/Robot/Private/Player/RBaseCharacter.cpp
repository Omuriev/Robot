// LifeAfter. All Rights Reserved.

#include "Player/RBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/RCharacterMovementComponent.h"
#include "Components/RHealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

ARBaseCharacter::ARBaseCharacter(FObjectInitializer const& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<URCharacterMovementComponent>(CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<URHealthComponent>(TEXT("HealthComponent"));
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthTextComponent"));
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

void ARBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ARBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ARBaseCharacter::OnHealthChanged);
}

void ARBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ARBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ARBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ARBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ARBaseCharacter::StartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ARBaseCharacter::StopRunning);
}

void ARBaseCharacter::MoveForward(float Value)
{
    IsMovingForward = Value > 0.0f;

    if (Value == 0.0f)
        return;

    AddMovementInput(GetActorForwardVector(), Value);
}

void ARBaseCharacter::MoveRight(float Value)
{
    if (Value == 0.0f)
        return;

    AddMovementInput(GetActorRightVector(), Value);
}

void ARBaseCharacter::StartRunning()
{
    WantsToRun = true;
}

void ARBaseCharacter::StopRunning()
{
    WantsToRun = false;
}

bool ARBaseCharacter::IsRunning() const
{
    return !GetVelocity().IsZero() && WantsToRun == true && IsMovingForward;
}

float ARBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ARBaseCharacter::OnDeath()
{
    UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
}

void ARBaseCharacter::OnHealthChanged(float Health) 
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}
