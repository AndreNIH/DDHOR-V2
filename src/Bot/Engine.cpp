#include "Engine.h"
#include <spdlog/spdlog.h>
#include "Deductor/DerDeductor.h"
#include "ExecLogic/FrameBackend.h"
#include "ExecLogic/XPosBackend.h"
/*void Bot::importMacro(const std::string& inFilename){
    spdlog::info("Attempting to import macro file: {}", inFilename);
    auto deserializer = getCompatibleDeserializer(inFilename);
    if(deserializer == nullptr){
       //do nothing for the moment being
       spdlog::warn("No deserializer was found");
       return;
    }
    try{
        this->runDeserializer(deserializer.get());
    }catch(const Deserializer::DerError& ex){
        spdlog::error(ex.what());
    }

}


void Bot::exportMacro(const std::string& outFilename){
    //auto ser = std::make_unique<Serializer::V2>();
    //auto botJson = runSerializer(ser.get());
    

}


void Bot::setMode(BotMode mode){
    if(mode == BotMode::kFrames){
        _player1.setBackend(std::make_unique<FrameBackend>());
        _player2.setBackend(std::make_unique<FrameBackend>());
    }else{
        _player1.setBackend(std::make_unique<XPosBackend>());
        _player2.setBackend(std::make_unique<XPosBackend>());
    }
}*/

std::unique_ptr<PlayerInput> BotPlayer::generateInputObject(){
    auto inputObject = std::make_unique<PlayerInput>();
    if(_isPlayer2) inputObject->setPlayer2();
    return inputObject;
}

void BotPlayer::insertClick(){
    auto pushCommand = std::make_unique<DoPress>(generateInputObject());
    _inputs->insertCommand(std::move(pushCommand));
}

void BotPlayer::insertRelease(){
    auto releaseCommand = std::make_unique<DoPress>(generateInputObject());
    _inputs->insertCommand(std::move(releaseCommand));
}

void BotPlayer::rewindActions(){
    _inputs->rewindQueue();
}

void BotPlayer::setCommandBackend(std::unique_ptr<CommandBackend>&& backend){
    _inputs = std::move(backend);
    if(_isPlayer2) _inputs->setPurpose(BackendPurpose::PLAYER_2);
    else _inputs->setPurpose(BackendPurpose::PLAYER_1);
}

void Bot::setBotBackend(BackendType backendId){
    std::unique_ptr<CommandBackend> backend = nullptr;
    if(backendId == BackendType::FRAMES) backend = std::make_unique<FrameBackend>();
    else if(backendId == BackendType::XPOS) backend = std::make_unique<XPosBackend>();
    else if(backendId == BackendType::PHYSICS) throw std::runtime_error{"not implemented"};
    _player1.setCommandBackend(std::move(backend));
    _player2.setCommandBackend(std::move(backend));
    //_comman.setCommandBackend() //to-be implemented    
}

void Bot::insertClick(TargetPlayer player){
    BotPlayer& target = player == TargetPlayer::PLAYER_1
        ? _player1
        : _player2;
    target.insertClick();   
}

void Bot::insertRelease(TargetPlayer player){
    BotPlayer& target = player == TargetPlayer::PLAYER_1
        ? _player1
        : _player2;
    target.insertRelease();   
}

void Bot::rewind(){
    _player1.rewindActions();
    _player2.rewindActions();
}

void Bot::update(){

}

bool Bot::importMacro(const std::string& inFilename){
    auto deserializer = getCompatibleDeserializer(inFilename);
    if(deserializer == nullptr){
        spdlog::warn("No suitable deserializer could be found for {}", inFilename);
        return false;
    }

    try{
        deserializer->deserialize(this);
        return true;
    }catch(const Deserializer::DerError& ex){
        spdlog::error("Exception caught. {} at line {}.\nDetails: {}", __FILE__, __LINE__, ex.what());
        return false;
    }
    

}

bool Bot::exportMacro(const std::string& outFilename){
    return false;
}


