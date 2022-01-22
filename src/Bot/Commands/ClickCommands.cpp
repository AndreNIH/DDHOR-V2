#include "ClickCommands.h"
#include <gd.h>
#include <spdlog/spdlog.h>
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
    spdlog::info("Executing DoPress::execute, Actor object at address");
    if(_actor == nullptr) spdlog::error("Attempted to perform action with null actor");
    else _actor->holdClick();
}

CommandID DoPress::type() const{
    return CommandID::CLICK;
}

void DoPress::bind(std::unique_ptr<PlayerInput>& command){
    spdlog::info("DoPress::bind, binding command PlayerInput, address={0:x}", (void*)command.get());
    _actor = std::move(command);
}

DoPress::DoPress(std::unique_ptr<PlayerInput>& command){
    bind(command);
}

//=======================================
//  DoRelease
//=======================================
void DoRelease::execute(){
    spdlog::info("Executing DoRelease::execute, Actor object at address");
    if(_actor == nullptr) spdlog::error("Attempted to perform action with null actor");
    else _actor->releaseClick();
}

CommandID DoRelease::type() const{
    return CommandID::RELEASE;
}


void DoRelease::bind(std::unique_ptr<PlayerInput>& command){
    spdlog::info("DoRelease::bind, binding command PlayerInput, address={0:x}", (void*)command.get());
    _actor = std::move(command);
}

DoRelease::DoRelease(std::unique_ptr<PlayerInput>& command){
    bind(command);
}

