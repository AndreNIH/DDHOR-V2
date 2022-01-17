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

enum class BackendType{
    XPOS,
    FRAMES,
    PHYSICS
};

enum class TargetPlayer{
    PLAYER_1,
    PLAYER_2
};

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

class CommandExecuter{
private:
    std::unique_ptr<CommandBackend> _commands = nullptr;

public:
    void setCommandsBackend(std::unique_ptr<CommandBackend>&& backend);
    void insertCommand(std::unique_ptr<BaseCommand>&& command);
    void rewindCommands();
};

class Bot{
    BotPlayer _player1;
    BotPlayer _player2;
    
public:
    void setBotBackend(BackendType backendId);
    void insertClick(TargetPlayer player);
    void insertRelease(TargetPlayer player);
    void rewind();
    void update();
    Bot() : _player1(false), _player2(true){}
    
};