// Zuzabr Games 2022 All Rights Reserved

#include "Core/BorderActor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "Core/EdibleSpriteActor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Core/EdibleGM.h"
#include "Engine/DataTable.h"
#include "Core/CollectableSpriteActor.h"
#include "Core/EdibleGameInstance.h"

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

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(SpringArmComponent);

    
}

void ABorderActor::BeginPlay()
{
    if (GetWorld())
    {
        const auto GameInst = GetWorld()->GetGameInstance<UEdibleGameInstance>();
        if (GameInst)
        {
            UE_LOG(LogTemp, Display, TEXT("GameInst Settings"));
            CurrentGameTheme = GameInst->GetGameTheme();
            BackgroundSprite->SetSprite(GetBackgroundSprite());
            EatableOnLeft = GameInst->GetEatableOnLeft();
        }
    }
 
    Super::BeginPlay();

    LeftBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnLeftBorderBeginOverlap);
    RightBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnRightBorderBeginOverlap);
    BottomBorder->OnComponentBeginOverlap.AddDynamic(this, &ABorderActor::OnBottomBorderBeginOverlap);

    CameraComponent->SetAspectRatio(768.f / 1024.f);
    SetActorsToSpawn(CurrentGameTheme);

    if (GetWorld())
    {
        GameMode = Cast<AEdibleGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnGameStarted.AddUObject(this, &ABorderActor::StartGameSession);
        }
    }
    
}

void ABorderActor::StartGameSession()
{    
    

    SetActorsToSpawn(CurrentGameTheme);
    StartSpawnObjects();
}

UPaperSprite* ABorderActor::GetBackgroundSprite() const
{
    if (!BackgroundThemes.Contains(CurrentGameTheme)) return nullptr;
    const auto Background = BackgroundThemes[CurrentGameTheme];
    return (Background != nullptr) ? Background : nullptr;
}

void ABorderActor::SetActorsToSpawn(EGameTheme Theme)
{

    if (SpawnActorDT == nullptr) return;
    FallingActorsToSpawn.Empty();
   
    static const FString DT_String = FString("Default");

    for (const auto& RowName : SpawnActorDT->GetRowNames())
    {
        const auto ActorInfo = SpawnActorDT->FindRow<FSpawnActorInfo>(RowName, DT_String, true);

        if (!ActorInfo) continue;

        if (Theme == EGameTheme::All)
        {
            if (ActorInfo->SpawnActorType == ESpawnActorType::FallingActors)
            {
                FallingActorsToSpawn.Add(*ActorInfo);
            }
            
        }
        else 
        {
            if ((ActorInfo->GameTheme == EGameTheme::All || ActorInfo->GameTheme == Theme) &&
                ActorInfo->SpawnActorType == ESpawnActorType::FallingActors)
            {
                FallingActorsToSpawn.Add(*ActorInfo);
            }
            
        }
    }
    
}

void ABorderActor::StartSpawnObjects()
{
    if (!(GetWorldTimerManager().IsTimerActive(FallingObjectsTimerHandle)))
    {
        GetWorldTimerManager().SetTimer(FallingObjectsTimerHandle, this, &ABorderActor::SpawnFallingObjects, FallingSpawnRate, true);
    }

    if (!(GetWorldTimerManager().IsTimerActive(CollectablesTimerHandle)))
    {
        GetWorldTimerManager().SetTimer(CollectablesTimerHandle, this, &ABorderActor::SpawnCollectables, CollectablesSpawnRate, true, 7.0f);
    }
   
}

void ABorderActor::StopSpawnObjects()
{
    GetWorldTimerManager().ClearTimer(FallingObjectsTimerHandle);
    GetWorldTimerManager().ClearTimer(CollectablesTimerHandle);
}

void ABorderActor::SpawnFallingObjects()
{

    int32 RandomIndex = FMath::RandRange(0, FallingActorsToSpawn.Num() - 1);
    if (!FallingActorsToSpawn.IsValidIndex(RandomIndex)) return;

    float X_Spawn = FMath::RandRange(X_Min, X_Max);

    FTransform ActorSpawnTransform;
    ActorSpawnTransform.SetLocation(FVector(X_Spawn, Y_Spawn, Z_Spawn));
    ActorSpawnTransform.Rotator() = ActorSpawnTransform.Rotator().ZeroRotator;
    ActorSpawnTransform.SetScale3D(FVector(1.5f));
    
    if (!GetWorld()) return;
    const auto Actor = GetWorld()->SpawnActorDeferred<AEdibleSpriteActor>(EdibleSpriteClass, ActorSpawnTransform);
    if (Actor)
    {
        Actor->SetActorInfo(&(FallingActorsToSpawn[RandomIndex]));
        UGameplayStatics::FinishSpawningActor(Actor, ActorSpawnTransform);
    }
}

void ABorderActor::SpawnCollectables()
{
    int32 RandomIndex = FMath::RandRange(0, CollectablesClasses.Num() - 1);
    if (!CollectablesClasses.IsValidIndex(RandomIndex)) return;

    float X_Spawn = FMath::RandRange(X_Min, X_Max);
    float Z_Collectable = FMath::RandRange(Z_Min, Z_Max);

    FTransform ActorSpawnTransform;
    ActorSpawnTransform.SetLocation(FVector(X_Spawn, Y_Spawn, Z_Collectable));
    ActorSpawnTransform.Rotator() = ActorSpawnTransform.Rotator().ZeroRotator;
    ActorSpawnTransform.SetScale3D(FVector(1.3f));

    if (!GetWorld()) return;
    const auto Actor =
        GetWorld()->SpawnActorDeferred<ACollectableSpriteActor>(CollectablesClasses[RandomIndex], ActorSpawnTransform);
    if (Actor)
    {       
        UGameplayStatics::FinishSpawningActor(Actor, ActorSpawnTransform);
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
            if (GameMode)
            {
                GameMode->AddRightEatableItems(1);
            }
            
        }
        else
        {
            if (GameMode)
            {
                GameMode->AddWrongEatableItems(1);
            }
        }
    }
    else
    {
        if (bEatable)
        {
            if (GameMode)
            {
                GameMode->AddWrongEatableItems(1);
            }
        }
        else
        {
            if (GameMode)
            {
                GameMode->AddRightEatableItems(1);
            }
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
            if (GameMode)
            {
                GameMode->AddWrongNonEatableItems(1);
            }
        }
        else
        {
            if (GameMode)
            {
                GameMode->AddRightNonEatableItems(1);
            }
        }
    }
    else
    {
        if (bEatable)
        {
            if (GameMode)
            {
                GameMode->AddRightNonEatableItems(1);
            }
        }
        else
        {
            if (GameMode)
            {
                GameMode->AddWrongNonEatableItems(1);
            }
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
    if (GameMode)
    {
        GameMode->AddMissedItems(1);
    }
    OverlappedActor->IntendToDestroy();
}
