// Zuzabr Games 2022 All Rights Reserved


#include "Core/EdiblePlayerController.h"
#include "Core/EdibleSpriteActor.h"
#include "Kismet/GameplayStatics.h"
#include "Core/BorderActor.h"
#include "Core/SpawnableSpriteActor.h"

AEdiblePlayerController::AEdiblePlayerController()
{
    SetShowMouseCursor(true);
}

void AEdiblePlayerController::BeginPlay()
{
    Super::BeginPlay();

    const auto Border = Cast<ABorderActor>(UGameplayStatics::GetActorOfClass(this, ABorderActor::StaticClass()));
    if (!Border)
    {
        UE_LOG(LogTemp, Warning, TEXT("BorderIsNotFound"));
        return;
    }
    SetViewTarget(Border);
}

void AEdiblePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AEdiblePlayerController::StartCarry);
    InputComponent->BindTouch(EInputEvent::IE_Released, this, &AEdiblePlayerController::StopCarry);
        
}

void AEdiblePlayerController::StartCarry(ETouchIndex::Type FingerIndex, FVector Location)
{
    
    FHitResult HitResult;
    if (!(GetHitResultUnderFingerByChannel(FingerIndex, ETraceTypeQuery::TraceTypeQuery1, false, HitResult))) return;
 
    const auto HitComp = HitResult.GetComponent();
    if (!HitComp) return;

    if(HitComp->IsSimulatingPhysics())
    {
        const auto EatableActor = Cast<AEdibleSpriteActor>(HitResult.GetActor());
        if (!EatableActor) return;
        EatableActor->StartToGrabActor(HitComp, HitResult.Location, FingerIndex);       
        GrabbedActors.Add(FingerIndex, EatableActor);       
    }
    else
    {
        const auto SpawnableActor = Cast<ASpawnableSpriteActor>(HitResult.GetActor());
        if (!SpawnableActor) return;
        SpawnableActor->StartInteract();
    }
        
}

void AEdiblePlayerController::StopCarry(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (GrabbedActors.Num()==0) return;
    if(GrabbedActors.Contains(FingerIndex))
    {
        GrabbedActors[FingerIndex]->StopGrabActor();
        GrabbedActors.Remove(FingerIndex);
    }
}



