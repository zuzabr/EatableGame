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
class UPaperSpriteComponent;
class UCameraComponent;
class USpringArmComponent;
class UDataTable;

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

    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    FVector2D GetBackgroundSize() const;

    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    inline int32 GetWrongEatableItems() const { return WrongEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    inline int32 GetRightEatableItems() const { return RightEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    inline int32 GetWrongNonEatableItems() const { return WrongNonEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    inline int32 GetRightNonEatableItems() const { return RightNonEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    inline int32 GetMissedItems() const { return MissedItems; }
    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    inline int32 GetExp() const { return Exp; }
    UFUNCTION(BlueprintCallable, Category = "BorderActor")
    inline int32 GetCoins() const { return Coins; };

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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

private:
    TArray<FSpawnActorInfo> ActorsToSpawn;
    TArray<USceneComponent*> SpawnPoints;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    EGameTheme CurrentGameTheme = EGameTheme::Farm;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    bool EatableOnLeft = true;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UDataTable* SpawnActorDT;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    float SpawnRate{1.0f};

    FTimerHandle SpawnObjectsTimerHandle;

    void SetFallingActorsToSpawn(EGameTheme Theme = EGameTheme::Farm);
    void SpawnObjects();

    UFUNCTION()
    void OnLeftBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnRightBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnBottomBorderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    int32 WrongEatableItems{0};
    int32 RightEatableItems{0};

    int32 WrongNonEatableItems{0};
    int32 RightNonEatableItems{0};

    int32 MissedItems{0};

    int32 Exp{0};
    int32 Coins{0};

};
