// Zuzabr Games 2022 All Rights Reserved


#include "Core/EdiblePlayerController.h"
#include "Core/EdibleSpriteActor.h"
#include "Kismet/GameplayStatics.h"
#include "Core/BorderActor.h"

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
   
    const auto HitActor = HitResult.GetActor();
    if (!HitActor) return;
    const auto EatableActor = Cast<AEdibleSpriteActor>(HitActor);
    const auto HitComp = HitResult.GetComponent();
    if (!EatableActor || !HitComp) return;

    if(HitComp->IsSimulatingPhysics())
    {
        
        EatableActor->StartToGrabActor(HitComp, HitResult.Location, FingerIndex);       
        GrabbedActors.Add(FingerIndex, EatableActor);       
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



