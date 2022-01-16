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

    std::unique_ptr<PlayerInput>generateInputObject();

public:
    void insertClick();
    void insertRelease();
    void rewindActions();
    void setCommandBackend(std::unique_ptr<CommandBackend>&& backend);
    BotPlayer(bool isP2) : _isPlayer2(isP2){}
};

class Bot{
    BotPlayer _player1;
    BotPlayer _player2;
    
public:
    Bot() : _player1(false), _player2(true){}
    std::pair<BotPlayer&, BotPlayer&> getPlayers();
};