// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EdibleCoreTypes.h"
#include "BorderActor.generated.h"

class UBoxComponent;
class USceneComponent;
class AEdibleSpriteActor;
class ACollectableSpriteActor;
class UPaperSpriteComponent;
class UCameraComponent;
class USpringArmComponent;
class UDataTable;
class UPaperSprite;
class AEdibleGM;

UCLASS()
class EDIBLEGAME_API ABorderActor : public AActor
{
    GENERATED_BODY()

public:
    ABorderActor();
    void ApplyGameSettings(EGameTheme GameTheme, bool EatableIsOnTheLeft);
    void StartSpawnObjects();
    void StopSpawnObjects();

    UFUNCTION()
    void StartGameSession();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UPaperSpriteComponent* BackgroundSprite;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* LeftBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* RightBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TopBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UBoxComponent* BottomBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;


    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    TSubclassOf<AEdibleSpriteActor> EdibleSpriteClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (NoElementDuplicate), Category = "Settings")
    TArray<TSubclassOf<ACollectableSpriteActor>> CollectablesClasses;
   
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
    float Y_Spawn = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float Z_Spawn = 4500.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float Z_Max = 3000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float Z_Min = -3000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float X_Min = -1970.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    float X_Max = 1970.0f;

private:
    TArray<FSpawnActorInfo> FallingActorsToSpawn;
    AEdibleGM* GameMode;
    
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    EGameTheme CurrentGameTheme = EGameTheme::Fruits;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    bool EatableOnLeft = true;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UDataTable* SpawnActorDT;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    float FallingSpawnRate{1.0f};

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    float CollectablesSpawnRate{5.5f};

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UPaperSprite* SpritePointer;

    FTimerHandle FallingObjectsTimerHandle;
    FTimerHandle CollectablesTimerHandle;
  
    void SetActorsToSpawn(EGameTheme Theme = EGameTheme::All);
    void SpawnFallingObjects();
    void SpawnCollectables();

    UFUNCTION()
    void OnLeftBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnRightBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnBottomBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    


};
