// LifeAfter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class URHealthComponent;
class UTextRenderComponent;

UCLASS()
class ROBOT_API ARBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ARBaseCharacter(FObjectInitializer const& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    URHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    virtual void BeginPlay() override;


public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    bool WantsToRun;
    bool IsMovingForward = false;
    void MoveForward(float Value);
    void MoveRight(float Value);

    void StartRunning();
    void StopRunning();

    void OnDeath();
    void OnHealthChanged(float Health);
};
