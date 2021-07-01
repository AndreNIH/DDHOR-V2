#include "GameController.h"
#include <Speedhack.h>
#include <Engine/Manager.h>

float gSpeedHack  = 1.0;
bool  gGamePaused = false;
bool  gSuspended = false;


void GameController::setSpeed(float multiplier) {
    gSpeedHack = multiplier;
}

void GameController::setPaused(bool paused) {
    gGamePaused = paused;
}

float GameController::getSpeed() {return gSpeedHack;}

bool GameController::getPaused(){return  gSuspended ? false : gGamePaused;}

void GameController::suspend(){
    gSuspended = true;
    Speedhack::setSpeed(1.0);
}

void GameController::commit(){
    gSuspended = false;
    Speedhack::setSpeed(gSpeedHack);
}

