// Zuzabr Games 2022 All Rights Reserved


#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Menu/MenuGameMode.h"
#include "Core/EdibleGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnQuitGame);
    }

    if (SettingsButton)
    {
        SettingsButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnSettingsOpen);
    }
}

void UMainMenuWidget::OnStartGame()
{
    const auto GameInstance = GetShooterGameInstance();
    if (!GameInstance) return;

    UGameplayStatics::OpenLevel(this, GameInstance->GetGameLvlName());
}

void UMainMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnSettingsOpen()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->OpenSettingsMenu();
    }
}

UEdibleGameInstance* UMainMenuWidget::GetShooterGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UEdibleGameInstance>();
}
