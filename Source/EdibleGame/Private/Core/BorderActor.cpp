// Zuzabr Games 2022 All Rights Reserved

#include "Core/BorderActor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Core/EdibleSpriteActor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Core/EdibleGM.h"
#include "Engine/DataTable.h"

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

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ABorderActor::BeginPlay()
{
    Super::BeginPlay();

    LeftBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnLeftBorderBeginOverlap);
    RightBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnRightBorderBeginOverlap);
    BottomBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnBottomBorderBeginOverlap);

    const auto SpriteSize = GetBackgroundSize();
    CameraComponent->SetAspectRatio(SpriteSize.X / SpriteSize.Y);
    SetFallingActorsToSpawn(CurrentGameTheme);

    if (GetWorld())
    {
        const auto GameMode = Cast<AEdibleGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStarted.AddUObject(this, &ABorderActor::StartGameSession);
        }
    }
}

void ABorderActor::StartGameSession()
{
    ApplyGameSettings(CurrentGameTheme, true);
    StartSpawnObjects();
}

void ABorderActor::ApplyGameSettings(EGameTheme GameTheme, bool EatableIsOnTheLeft)
{
    if (CurrentGameTheme != GameTheme)
    {
        CurrentGameTheme = GameTheme;
        SetFallingActorsToSpawn(GameTheme);
    }
    EatableOnLeft = EatableIsOnTheLeft;
}

void ABorderActor::SetFallingActorsToSpawn(EGameTheme Theme)
{

    if (SpawnActorDT == nullptr) return;
    ActorsToSpawn.Empty();
    static const FString DT_String = FString("Default");

    for (const auto& RowName : SpawnActorDT->GetRowNames())
    {
        const auto ActorInfo = SpawnActorDT->FindRow<FSpawnActorInfo>(RowName, DT_String, true);

        if (!ActorInfo) continue;

        if (ActorInfo->GameTheme == Theme && ActorInfo->SpawnActorType == ESpawnActorType::FallingActors)
        {
            ActorsToSpawn.Add(*ActorInfo);
        }
    }
}

void ABorderActor::StartSpawnObjects()
{
    if (GetWorldTimerManager().IsTimerActive(SpawnObjectsTimerHandle)) return;
    GetWorldTimerManager().SetTimer(SpawnObjectsTimerHandle, this, &ABorderActor::SpawnObjects, SpawnRate, true);
}

void ABorderActor::StopSpawnObjects()
{
    GetWorldTimerManager().ClearTimer(SpawnObjectsTimerHandle);
}

FVector2D ABorderActor::GetBackgroundSize() const
{
    return BackgroundSprite->GetSprite()->GetSourceSize();
}

void ABorderActor::SpawnObjects()
{

    int32 RandomIndex = FMath::RandRange(0, ActorsToSpawn.Num() - 1);
    if (!ActorsToSpawn.IsValidIndex(RandomIndex)) return;

    int32 RandomPoint = FMath::RandRange(0, SpawnPoints.Num() - 1);
    if (!SpawnPoints.IsValidIndex(RandomPoint)) return;

    if (!GetWorld()) return;

    const auto Actor =
        GetWorld()->SpawnActorDeferred<AEdibleSpriteActor>(EdibleSpriteClass, SpawnPoints[RandomPoint]->GetComponentTransform());
    if (Actor)
    {

        ++Exp;
        Actor->SetActorInfo(&(ActorsToSpawn[RandomIndex]));
        UGameplayStatics::FinishSpawningActor(Actor, SpawnPoints[RandomPoint]->GetComponentTransform());
    }
}

void ABorderActor::OnLeftBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const auto OverlappedActor = Cast<AEdibleSpriteActor>(OtherActor);
    if (!OverlappedActor) return;

    const auto bEatable = OverlappedActor->GetIsEatable();
    if (EatableOnLeft)
    {
        if (bEatable)
        {
            ++RightEatableItems;
        }
        else
        {
            ++WrongEatableItems;
        }
    }
    else
    {
        if (bEatable)
        {
            ++WrongEatableItems;
        }
        else
        {
            ++RightEatableItems;
        }
    }
    OverlappedActor->IntendToDestroy();
    return;
}

void ABorderActor::OnRightBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const auto OverlappedActor = Cast<AEdibleSpriteActor>(OtherActor);
    if (!OverlappedActor) return;

    const auto bEatable = OverlappedActor->GetIsEatable();
    if (EatableOnLeft)
    {
        if (bEatable)
        {
            ++WrongNonEatableItems;
        }
        else
        {
            ++RightNonEatableItems;
        }
    }
    else
    {
        if (bEatable)
        {
            ++RightNonEatableItems;
        }
        else
        {
            ++WrongNonEatableItems;
        }
    }
    OverlappedActor->IntendToDestroy();
    return;
}

void ABorderActor::OnBottomBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto OverlappedActor = Cast<AEdibleSpriteActor>(OtherActor);
    if (!OverlappedActor) return;
    ++MissedItems;
    OverlappedActor->IntendToDestroy();
}
