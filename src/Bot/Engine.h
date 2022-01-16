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

/*class FakePlayer : private Deserializable, Serializable{
private:
    std::unique_ptr<CommandBackend> _behaviour = nullptr;
    const bool _isP2;

public:
    void insertAction(Action action){_behaviour->insertAction(playLayer);};
    void rewindActionQueue(PlayLayer* playLayer){_behaviour->rewindActionQueue(playLayer);}
    void reset() {_behaviour->reset();}

    //=======================================================
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject){
        _behaviour->runDeserializer(deserializaitionObject);
    }

    nlohmann::json runSerializer(Serializer::BotSerializer* serializationObject){
        return _behaviour->runSerializer(serializationObject);
    }

    void setBackend(std::unique_ptr<CommandBackend>&& backend){
        _behaviour = std::move(backend);
        if(_isP2) _behaviour->setPlayer2Logic();
    }

    FakePlayer(bool isP2) : _isP2(isP2){}
};


enum class BotMode{
    kFrames,
    kXPos
};

class Bot :  private Deserializable, Serializable{
private:
    FakePlayer _player1;
    FakePlayer _player2;
    float _fps=0;
    BotMode _mode;

    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override{
        deserializaitionObject->deserialize(this);
        _player1.runDeserializer(deserializaitionObject);
        _player2.runDeserializer(deserializaitionObject);
    }

    nlohmann::json runSerializer(Serializer::BotSerializer* serializationObject) override{
        return serializationObject->serialize(this);
    }

public:

    void importMacro(const std::string& inFilename);
    void exportMacro(const std::string& outFilename);
    
    void setFPSValue(float fps) {_fps = fps;}
    float getFPSValue() const {return _fps;}
    
    void setMode(BotMode mode);
    BotMode getMode() const {return _mode;}
    //std::pair<FakePlayerProxy, FakePlayerProxy> player();
    const std::pair<FakePlayer& ,FakePlayer&> player(){
        return {_player1, _player2};
    }

    Bot() : _player1(false), _player2(true) {}


};*/

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