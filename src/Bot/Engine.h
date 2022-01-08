#pragma once
#include "Behaviour/BotBehavior.h"
#include "Deserializer/Deserialization.h"
#include "Deserializer/Deseriliazble.h"
#include "Serializer/Serializble.h"
#include "Serializer/Serialization.h"


#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <memory>


class FakePlayer : private Deserializable, Serializable{
private:
    std::unique_ptr<BotBackend> _behaviour = nullptr;
    const bool _isP2;

public:
    void insertAction(PlayLayer* playLayer){_behaviour->insertAction(playLayer);};
    void rewindActionQueue(PlayLayer* playLayer){_behaviour->rewindActionQueue(playLayer);}
    void reset() {_behaviour->reset();}

    //=======================================================
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject){
        _behaviour->runDeserializer(deserializaitionObject);
    }

    nlohmann::json runSerializer(Serializer::BotSerializer* serializationObject){
        return _behaviour->runSerializer(serializationObject);
    }

    void setBackend(std::unique_ptr<BotBackend>&& backend){
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


};