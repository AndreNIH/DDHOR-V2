#include "ClickCommands.h"
#include <gd.h>
#include <spdlog/spdlog.h>


//=======================================
//  DoPress
//=======================================
void DoPress::execute(){
    spdlog::info("Executing DoPress::execute");
    const bool flip = gd::GameManager::sharedState()->getGameVariable("0010");
    gd::PlayLayer::get()->pushButton(0, (!_isP2) ^ flip);
}

CommandID DoPress::type() const{
    return CommandID::CLICK;
}

DoPress::DoPress(bool p2) : _isP2(p2){}

//=======================================
//  DoRelease
//=======================================
void DoRelease::execute(){
    spdlog::info("Executing DoRelease::execute, Actor object at address");
    const bool flip = gd::GameManager::sharedState()->getGameVariable("0010");
    gd::PlayLayer::get()->releaseButton(0, (!_isP2) ^ flip);
}

CommandID DoRelease::type() const{
    return CommandID::RELEASE;
}

DoRelease::DoRelease(bool p2) : _isP2(p2){}