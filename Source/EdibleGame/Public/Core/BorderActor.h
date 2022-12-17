// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EdibleCoreTypes.h"
#include "BorderActor.generated.h"

class UBoxComponent;
class USceneComponent;
class UPaperSprite;
class AEdibleSpriteActor;

UCLASS()
class EDIBLEGAME_API ABorderActor : public AActor
{
    GENERATED_BODY()

public:
    ABorderActor();
    void ApplyGameSettings(EGameTheme GameTheme, bool EatableIsOnTheLeft);
    void StartSpawnObjects();
    void StopSpawnObjects();
    

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UPaperSprite* BackSprite;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* LeftBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* RightBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TopBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* BottomBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* SpawnPoint1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* SpawnPoint2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* SpawnPoint3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* SpawnPoint4;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* SpawnPoint5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* Root;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    TSubclassOf<AEdibleSpriteActor> EdibleSpriteClass;

private:
    TArray<FSpawnActorInfo> ActorsToSpawn;
    TArray<USceneComponent*> SpawnPoints;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    EGameTheme CurrentGameTheme = EGameTheme::Farm;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    bool EatableOnLeft = true;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    FDataTableRowHandle SpawnActorDT;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    float SpawnRate{1.5f};

    FTimerHandle SpawnObjectsTimerHandle;

    void SetFallingActorsToSpawn(EGameTheme Theme = EGameTheme::Farm);
    void SpawnObjects();

    UFUNCTION()
    void OnLeftRightBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void OnBottomBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
