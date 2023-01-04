// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameProgressWidget.generated.h"

class UButton;
class AEdibleGM;

UCLASS()
class EDIBLEGAME_API UGameProgressWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UButton* PauseButton;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Eatable GM")
    AEdibleGM* GameMode;

    UFUNCTION(BlueprintCallable)
    bool GetEatableOnLeft() const;

private:
    UFUNCTION()
    void OnPauseSet();

};
