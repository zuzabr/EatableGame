// Zuzabr Games 2022 All Rights Reserved


#include "UI/RestartWidget.h"
#include "Components/Button.h"
#include "Core/EdibleGameInstance.h"
#include "Kismet/GameplayStatics.h"


void URestartWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (RestartButton)
    {
        RestartButton->OnPressed.AddDynamic(this, &URestartWidget::RestartGame);
    }
}

void URestartWidget::RestartGame()
{
    if (!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<UEdibleGameInstance>();
    if (!GameInstance) return;

    if (GameInstance->GetGameLvlName().IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("Menu Level Name is None"));
        return;
    }

    UGameplayStatics::OpenLevel(this, GameInstance->GetGameLvlName());
}
