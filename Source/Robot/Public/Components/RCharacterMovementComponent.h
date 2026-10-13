// LifeAfter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RCharacterMovementComponent.generated.h"

UCLASS()
class ROBOT_API URCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", class = "10.0"))
    float RunSpeedMultiplier = 1.2f;

    virtual float GetMaxSpeed() const override;
};
