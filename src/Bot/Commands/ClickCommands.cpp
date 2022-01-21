#include "ClickCommands.h"
#include <gd.h>
//=======================================
//  PlayerInput
//=======================================
void PlayerInput::holdClick(){
    const bool flip = gd::GameManager::sharedState()->getGameVariable("0010");
    gd::PlayLayer::get()->pushButton(0, (!_isP2) ^ flip);
}

void PlayerInput::releaseClick(){
    const bool flip = gd::GameManager::sharedState()->getGameVariable("0010");
    gd::PlayLayer::get()->releaseButton(0, (!_isP2) ^ flip);
}

void PlayerInput::setPlayer2(){
    _isP2 = true;
}

//=======================================
//  DoPress
//=======================================
void DoPress::execute(){
    assert(_actor != nullptr, "Comamnd target cannot be nullptr");
    _actor->holdClick();
}

CommandID DoPress::type() const{
    return CommandID::CLICK;
}

void DoPress::bind(std::unique_ptr<PlayerInput>& command){
    _actor = std::move(command);
}

DoPress::DoPress(std::unique_ptr<PlayerInput>& command){
    bind(command);
}

//=======================================
//  DoRelease
//=======================================
void DoRelease::execute(){
    assert(_actor != nullptr, "Comamnd target cannot be nullptr");
    _actor->releaseClick();
}

CommandID DoRelease::type() const{
    return CommandID::RELEASE;
}


void DoRelease::bind(std::unique_ptr<PlayerInput>& command){
    _actor = std::move(command);
}

DoRelease::DoRelease(std::unique_ptr<PlayerInput>& command){
    bind(command);
}

