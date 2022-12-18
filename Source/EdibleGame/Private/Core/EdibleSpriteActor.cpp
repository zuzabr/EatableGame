// Zuzabr Games 2022 All Rights Reserved

#include "Core/EdibleSpriteActor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Core/EdiblePlayerController.h"

AEdibleSpriteActor::AEdibleSpriteActor()
{
    PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");
}

void AEdibleSpriteActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bCarried)
    {
        UpdateActorLocation();
    }
}

bool AEdibleSpriteActor::GetIsEatable() const
{
    return SpawnActorInfo != nullptr ? SpawnActorInfo->bEatable : false;
}

void AEdibleSpriteActor::StartToGrabActor(UPrimitiveComponent* Comp, FVector Location, ETouchIndex::Type FingerIndex, bool Grab)
{
    bCarried = Grab;
    Finger = FingerIndex;
    FName Name = NAME_None;
    PhysicsHandle->GrabComponentAtLocation(Comp, Name, (Cast<USceneComponent>(Comp))->GetComponentLocation());
}

void AEdibleSpriteActor::StopGrabActor(bool Grab)
{
    bCarried = Grab;
    PhysicsHandle->ReleaseComponent();
}

// Need To Set Location Correctly
void AEdibleSpriteActor::UpdateActorLocation()
{
    const auto Controller = Cast<AEdiblePlayerController>(GetWorld()->GetFirstPlayerController());
    if (!Controller) return;
    
    float XLoc;
    float YLoc;

    Controller->GetInputTouchState(Finger, XLoc, YLoc, bCarried);
    if (bCarried)
    {
        FVector Loc;
        Loc.X = XLoc;
        Loc.Z = YLoc;
        Loc.Y = GetActorLocation().Y;
        PhysicsHandle->SetTargetLocation(Loc);
    }
    else
    {
        StopGrabActor();
    }
    
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
