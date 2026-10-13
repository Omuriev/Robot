// LifeAfter. All Rights Reserved.


#include "Dev/RDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ARDevDamageActor::ARDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);
}

void ARDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFUllDamage);
}



