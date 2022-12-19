// Zuzabr Games 2022 All Rights Reserved

#include "Core/EdibleSpriteActor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Core/EdiblePlayerController.h"

AEdibleSpriteActor::AEdibleSpriteActor()
{
    PrimaryActorTick.bCanEverTick = false;
    PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");
}

void AEdibleSpriteActor::BeginPlay()
{
    Super::BeginPlay();
    Controller = Cast<AEdiblePlayerController>(GetWorld()->GetFirstPlayerController());
}

void AEdibleSpriteActor::StartToGrabActor(UPrimitiveComponent* Comp, FVector Location, ETouchIndex::Type FingerIndex)
{
    
    Finger = FingerIndex;
    PhysicsHandle->GrabComponentAtLocation(Comp, NAME_None, Location);

    GetWorldTimerManager().SetTimer(CarryTimerHandle, this, &AEdibleSpriteActor::UpdateActorLocation, 0.01f, true);
}

void AEdibleSpriteActor::StopGrabActor()
{
    PhysicsHandle->ReleaseComponent();
    GetWorldTimerManager().ClearTimer(CarryTimerHandle);
}

void AEdibleSpriteActor::UpdateActorLocation()
{
    Controller = Controller != nullptr ? Controller : Cast<AEdiblePlayerController>(GetWorld()->GetFirstPlayerController());

    if (!Controller) return;

    FVector Location;

    FHitResult HitResult;
    if (!(Controller->GetHitResultUnderFingerByChannel(Finger, ETraceTypeQuery::TraceTypeQuery1, false, HitResult))) return;
    Location = HitResult.Location;
    Location.Y = (Cast<USceneComponent>(PhysicsHandle->GrabbedComponent)->GetComponentLocation()).Y;
    PhysicsHandle->SetTargetLocation(Location);
}

UPaperSprite* AEdibleSpriteActor::GetEatableActorSprite() const
{
    if (SpawnActorInfo != nullptr && SpawnActorInfo->ItemSptite != nullptr)
    {
        return SpawnActorInfo->ItemSptite;
    }
    else
    {
        return ItemSptite;
    }
}

bool AEdibleSpriteActor::GetIsEatable() const
{
    return SpawnActorInfo != nullptr ? SpawnActorInfo->bEatable : false;
}
