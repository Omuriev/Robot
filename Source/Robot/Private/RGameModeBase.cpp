// LifeAfter. All Rights Reserved.

#include "RGameModeBase.h"
#include "Player/RBaseCharacter.h"
#include "Player/RPlayerController.h"

ARGameModeBase::ARGameModeBase() {
    DefaultPawnClass = ARBaseCharacter::StaticClass();
    PlayerControllerClass = ARPlayerController::StaticClass();
}
