// Zuzabr Games 2022 All Rights Reserved

#include "Core/BorderActor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Core/EdibleSpriteActor.h"
#include "Kismet/GameplayStatics.h"


ABorderActor::ABorderActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>("Root");
    SetRootComponent(Root);
 
    BackgroundSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BackgroundBorder");
    BackgroundSprite->SetupAttachment(Root);

    LeftBorder = CreateDefaultSubobject<UBoxComponent>("LeftBorder");
    LeftBorder->SetupAttachment(BackgroundSprite);
    RightBorder = CreateDefaultSubobject<UBoxComponent>("RightBorder");
    RightBorder->SetupAttachment(BackgroundSprite);
    BottomBorder = CreateDefaultSubobject<UBoxComponent>("BottomBorder");
    BottomBorder->SetupAttachment(BackgroundSprite);
    TopBorder = CreateDefaultSubobject<UBoxComponent>("TopBorder");
    TopBorder->SetupAttachment(BackgroundSprite);

    LeftBorder->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    LeftBorder->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    LeftBorder->SetGenerateOverlapEvents(true);

    RightBorder->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    RightBorder->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    RightBorder->SetGenerateOverlapEvents(true);

    BottomBorder->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    BottomBorder->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BottomBorder->SetGenerateOverlapEvents(true);

    TopBorder->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    TopBorder->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    SpawnPoint1 = CreateDefaultSubobject<USceneComponent>("SpawnPoint1");
    SpawnPoint1->SetupAttachment(Root);
    SpawnPoint2 = CreateDefaultSubobject<USceneComponent>("SpawnPoint2");
    SpawnPoint2->SetupAttachment(Root);
    SpawnPoint3 = CreateDefaultSubobject<USceneComponent>("SpawnPoint3");
    SpawnPoint3->SetupAttachment(Root);
    SpawnPoint4 = CreateDefaultSubobject<USceneComponent>("SpawnPoint4");
    SpawnPoint4->SetupAttachment(Root);
    SpawnPoint5 = CreateDefaultSubobject<USceneComponent>("SpawnPoint5");
    SpawnPoint5->SetupAttachment(Root);
    
    SpawnPoints.Empty();
    SpawnPoints.Add(SpawnPoint1);
    SpawnPoints.Add(SpawnPoint2);
    SpawnPoints.Add(SpawnPoint3);
    SpawnPoints.Add(SpawnPoint4);
    SpawnPoints.Add(SpawnPoint5);

   
    
}

void ABorderActor::BeginPlay()
{
    Super::BeginPlay();

    LeftBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnLeftRightBorderBeginOverlap);
    RightBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnLeftRightBorderBeginOverlap);
    BottomBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnBottomBorderBeginOverlap);

    //*************************************************Initial Settings**********************************
    ApplyGameSettings(CurrentGameTheme, true);
    SetFallingActorsToSpawn(CurrentGameTheme);

    StartSpawnObjects();
}

void ABorderActor::ApplyGameSettings(EGameTheme GameTheme, bool EatableIsOnTheLeft)
{
    if(CurrentGameTheme != GameTheme)
    {
        CurrentGameTheme = GameTheme;
        SetFallingActorsToSpawn(GameTheme);
    }
    EatableOnLeft = EatableIsOnTheLeft;
}

void ABorderActor::SetFallingActorsToSpawn(EGameTheme Theme)
{

    if (SpawnActorDT.DataTable.IsNull()) return;
    UE_LOG(LogTemp, Display, TEXT("Data Table is not null"));

    ActorsToSpawn.Empty();
    static const FString DT_String = FString("Default");

    for (const auto& RowName : SpawnActorDT.DataTable->GetRowNames())
    {
        const auto ActorInfo = SpawnActorDT.DataTable->FindRow<FSpawnActorInfo>(RowName, DT_String, true);

        if (!ActorInfo) continue;

        if (ActorInfo->GameTheme == Theme && ActorInfo->SpawnActorType == ESpawnActorType::FallingActors)
        {
            ActorsToSpawn.Add(*ActorInfo);
        }
    }


}

void ABorderActor::StartSpawnObjects()
{
    GetWorldTimerManager().SetTimer(SpawnObjectsTimerHandle, this, &ABorderActor::SpawnObjects, SpawnRate, true);
}

void ABorderActor::StopSpawnObjects()
{
    GetWorldTimerManager().ClearTimer(SpawnObjectsTimerHandle);
}

void ABorderActor::SpawnObjects()
{
    int32 RandomIndex = FMath::RandRange(0, ActorsToSpawn.Num() - 1);
    if (!ActorsToSpawn.IsValidIndex(RandomIndex)) return;
    
    int32 RandomPoint = FMath::RandRange(0, SpawnPoints.Num() - 1);
    if (!SpawnPoints.IsValidIndex(RandomPoint)) return;

    if (!GetWorld()) return;
   
    const auto Actor = GetWorld()->SpawnActorDeferred<AEdibleSpriteActor>(EdibleSpriteClass, SpawnPoints[RandomPoint]->GetComponentTransform());
    if (Actor)
    {
        Actor->SetActorInfo(&(ActorsToSpawn[RandomIndex]));
        UGameplayStatics::FinishSpawningActor(Actor, SpawnPoints[RandomPoint]->GetComponentTransform());
    }
    

}

void ABorderActor::OnLeftRightBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const auto OverlappedActor = Cast<AEdibleSpriteActor>(OtherActor);
    if (!OverlappedActor) return;
    
    //*****************************Actor overlap left border******************************
    if(LeftBorder->IsOverlappingActor(OverlappedActor))
    {
        const auto ActorIsEatable = OverlappedActor->GetIsEatable();
        if (EatableOnLeft)
        {
            if (ActorIsEatable)
            {
                UE_LOG(LogTemp, Display, TEXT("You are Right!"));
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("You are Wrong!"));
            }
        }
        else
        {
            if (ActorIsEatable)
            {
                UE_LOG(LogTemp, Display, TEXT("You are Wrong!"));
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("You are Right!"));
            }
        }
        OverlappedActor->SetLifeSpan(2.f);//Change
        return;
    }
//*****************************Actor overlap left border******************************

//*****************************Actor overlap right border******************************
    if (RightBorder->IsOverlappingActor(OverlappedActor))
    {
        const auto ActorIsEatable = OverlappedActor->GetIsEatable();
        if (EatableOnLeft)
        {
            if (ActorIsEatable)
            {
                UE_LOG(LogTemp, Display, TEXT("You are Wrong!"));
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("You are Right!"));
            }
        }
        else
        {
            if (ActorIsEatable)
            {
                UE_LOG(LogTemp, Display, TEXT("You are Right!"));
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("You are Wrong!"));
            }
        }
        OverlappedActor->SetLifeSpan(2.f);//Change
        return;
    }

//*****************************Actor overlap right border******************************
}

void ABorderActor::OnBottomBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto OverlappedActor = Cast<AEdibleSpriteActor>(OtherActor);
    if (!OverlappedActor) return;
    UE_LOG(LogTemp, Display, TEXT("You loooose!"));
    OverlappedActor->SetLifeSpan(1.0f);//Change
}



