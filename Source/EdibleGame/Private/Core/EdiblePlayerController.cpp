// Zuzabr Games 2022 All Rights Reserved


#include "Core/EdiblePlayerController.h"
#include "Core/EdibleSpriteActor.h"



AEdiblePlayerController::AEdiblePlayerController()
{
    bEnableTouchOverEvents = true;

}

void AEdiblePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AEdiblePlayerController::StartCarry);
    InputComponent->BindTouch(EInputEvent::IE_Released, this, &AEdiblePlayerController::StopCarry);
    
    
}

void AEdiblePlayerController::StartCarry(ETouchIndex::Type FingerIndex, FVector Location)
{
    UE_LOG(LogTemp, Warning, TEXT("*****************************Touch*****************************"));
    FHitResult HitResult;
    if (!(GetHitResultUnderFingerByChannel(FingerIndex, ETraceTypeQuery::TraceTypeQuery1, false, HitResult)))
    {
        UE_LOG(LogTemp, Display, TEXT("*****************************Hit Nothing*****************************"));
        return;
    }

    const auto HitActor = HitResult.GetActor();
    if (!HitActor) return;
    const auto EatableActor = Cast<AEdibleSpriteActor>(HitActor);
    const auto HitComp = HitResult.GetComponent();
    if (!EatableActor || !HitComp) return;

    if(HitComp->IsSimulatingPhysics())
    {
        static FName Name = NAME_None;
        EatableActor->StartToGrabActor(HitComp, HitResult.Location, FingerIndex, true);       
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



