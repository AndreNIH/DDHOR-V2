#include "ClickCommands.h"
//=======================================
//  PlayerInput
//=======================================
void PlayerInput::holdClick(){

}

void PlayerInput::releaseClick(){

}

void PlayerInput::setPlayer2(){

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

DoPress::DoPress(std::unique_ptr<PlayerInput>& command){
    _actor = std::move(command);
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


DoRelease::DoRelease(std::unique_ptr<PlayerInput>& command){
    _actor = std::move(command);
}

