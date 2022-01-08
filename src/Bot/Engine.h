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
    BotBackend* _behaviour;
    

public:
    void insertAction(PlayLayer* playLayer){_behaviour->insertAction(playLayer);};
    void rewindActionQueue(PlayLayer* playLayer){_behaviour->rewindActionQueue(playLayer);}
    void reset() {_behaviour->reset();}


    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject){
        _behaviour->runDeserializer(deserializaitionObject);
    }

    nlohmann::json runSerializer(Serializer::BotSerializer* serializationObject){
        return _behaviour->runSerializer(serializationObject);
    }
};


enum class BotMode{
    kFrames,
    kXPos
};

class Bot :  private Deserializable, Serializable{
private:
    std::unique_ptr<FakePlayer> _player1;
    std::unique_ptr<FakePlayer> _player2;
    float _fps;
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
        return {*_player1.get(), *_player2.get()};
    }

};