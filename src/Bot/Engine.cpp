#include "Engine.h"
#include <spdlog/spdlog.h>
#include "Deductor/DerDeductor.h"
#include "Backend/FrameBackend.h"
#include "Backend/XPosBackend.h"
#include <spdlog/fmt/bin_to_hex.h>
#include <algorithm>
void BotPlayer::verifyPtrSafety(){
    if(_backend == nullptr){
        const std::string msg = "Attempted to access nulled backend object";
        throw std::runtime_error{msg};
    }
}

void BotPlayer::insertClick(){
    verifyPtrSafety();
    auto pushCommand = std::make_unique<DoPress>(_isPlayer2);;
    _backend->insertCommand(std::move(pushCommand));
}

void BotPlayer::insertRelease(){
    verifyPtrSafety();
    auto releaseCommand = std::make_unique<DoRelease>(_isPlayer2);
    _backend->insertCommand(std::move(releaseCommand));
}

void BotPlayer::rewindActions(){
    verifyPtrSafety();
    _backend->rewindQueue();
}

void BotPlayer::rollbackActions(){
    verifyPtrSafety();
    _backend->rollbackQueue();
}

void BotPlayer::executeActions(){
    verifyPtrSafety();
    _backend->executeCommands();
}

void BotPlayer::setCommandBackend(std::unique_ptr<CommandBackend>&& backend){
    spdlog::info("Setting BotPlayer command backend, addr={0:x}", (void*)backend.get());
    _backend = std::move(backend);
    if(_isPlayer2) _backend->setPurpose(BackendPurpose::PLAYER_2);
    else _backend->setPurpose(BackendPurpose::PLAYER_1);
}

#define ASSIGN_BACKEND(TARGET,TYPE) \
std::generate(TARGET.begin(), TARGET.end(), [](){return std::make_unique<TYPE>();})

void Bot::setBotBackend(BackendType backendId){
    std::array<std::unique_ptr<CommandBackend>,2> backend = {nullptr};
    if(backendId == BackendType::FRAMES) ASSIGN_BACKEND(backend, FrameBackend);
    else if(backendId == BackendType::XPOS) ASSIGN_BACKEND(backend, XPosBackend);
    else if(backendId == BackendType::FRAMES ) throw std::runtime_error{"not implemented"};    
    _player1.setCommandBackend(std::move(backend[0]));
    _player2.setCommandBackend(std::move(backend[1]));
    //_comman.setCommandBackend() //to-be implemented    
}

#undef ASSIGN_BACKEND

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

void Bot::rollback(){
    _player1.rollbackActions();
    _player2.rollbackActions();
}

void Bot::update(){
    _player1.executeActions();
    _player2.executeActions();
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

#include <cocos2d.h>
void Bot::setFPS(float fps){
    //Temporary, switch over to MVC
    _fps = fps;
    cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0/fps);
}
