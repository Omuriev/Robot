// LifeAfter. All Rights Reserved.


#include "Components/RCharacterMovementComponent.h"
#include "Player/RBaseCharacter.h"

float URCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ARBaseCharacter* Character = Cast<ARBaseCharacter>(GetPawnOwner());
    
    return Character && Character->IsRunning() ? MaxSpeed * RunSpeedMultiplier : MaxSpeed;
}