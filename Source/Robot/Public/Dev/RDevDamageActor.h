// LifeAfter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RDevDamageActor.generated.h"

UCLASS()
class ROBOT_API ARDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:
	ARDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFUllDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
