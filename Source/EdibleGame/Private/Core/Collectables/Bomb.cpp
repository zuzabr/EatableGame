// Zuzabr Games 2022 All Rights Reserved

#include "Core/Collectables/Bomb.h"
#include "Core/EdibleSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABomb::ABomb()
{
    OnDestroyed.AddDynamic(this, &ABomb::OnBombDestroyed);
}

void ABomb::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(2.0f);
}

void ABomb::OnBombDestroyed(AActor* DestroyedActor)
{
    if (bNeutralized) return;
    if (!GetWorld()) return;

    FVector BombLocation = DestroyedActor->GetActorLocation();
    TArray<FHitResult> HitResults;
    FCollisionShape Collision = FCollisionShape::MakeSphere(5000.f);
    bool bHit = GetWorld()->SweepMultiByChannel(HitResults, BombLocation, BombLocation, FQuat::Identity, ECC_Visibility, Collision);
    if (!bHit) return;
    // Working for this moment
    for (auto& Result : HitResults)
    {
        
        auto Actor = Cast<AEdibleSpriteActor>(Result.GetActor());
        if (Actor)
        {
            UE_LOG(LogTemp, Display, TEXT("BombDestroyed"));
            Actor->GetRenderComponent()->AddRadialImpulse(BombLocation, 2000.f, 5000.f, ERadialImpulseFalloff::RIF_Constant, true);
        }
        
    }
}

void ABomb::StartInteract()
{
    bNeutralized = false;
    Destroy();
}