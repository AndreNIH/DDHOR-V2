#include "Engine.h"
#include <spdlog/spdlog.h>
#include "Deductor/DerDeductor.h"

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