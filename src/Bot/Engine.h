#pragma once
#include "ExecLogic/CmdExecuterLogic.h"
#include "Deserializer/Deserialization.h"
#include "Deserializer/Deseriliazble.h"
#include "Serializer/Serializble.h"
#include "Serializer/Serialization.h"


#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <memory>

#include "Commands/ClickCommands.h"

class BotPlayer{
    
    std::unique_ptr<CommandBackend> _inputs = nullptr;
    const bool _isPlayer2;

    std::unique_ptr<PlayerInput>generateInputObject(){
        auto inputObject = std::make_unique<PlayerInput>();
        if(_isPlayer2) inputObject->setPlayer2();
        return inputObject;
    }
public:
    void insertClick(){
        auto pushCommand = std::make_unique<DoPress>(generateInputObject());
        _inputs->insertCommand(std::move(pushCommand));
    }
    void insertRelease(){
        auto releaseCommand = std::make_unique<DoPress>(generateInputObject());
        _inputs->insertCommand(std::move(releaseCommand));
    }
    
    void rewindActions(){
        _inputs->rewindQueue();
    }
    
    void setCommandBackend(std::unique_ptr<CommandBackend>&& backend){
        _inputs = std::move(backend);
        if(_isPlayer2) _inputs->setPurpose(BackendPurpose::PLAYER_2);
        else _inputs->setPurpose(BackendPurpose::PLAYER_1);
    }

    BotPlayer(bool isP2) : _isPlayer2(isP2){}
};


class Bot{
    BotPlayer _player1;
    BotPlayer _player2;
    
public:
    Bot() : _player1(false), _player2(true){}
};