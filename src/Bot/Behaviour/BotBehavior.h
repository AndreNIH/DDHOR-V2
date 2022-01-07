#pragma once
#include "../Deserializer/Deseriliazble.h"
#include "../Serializer/Serializble.h"
#include "Actions/Actions.h"

using PlayLayer = void;



class BotBackend : public Deserializable, public Serializable{    
private:

public:
    virtual void insertAction(PlayLayer* playLayer)=0;
    virtual void rewindActionQueue(PlayLayer* playLayer)=0;
    virtual void reset()=0;
    
    //Accept Methods
    //virtual void runSerializer(Deserializer::BotDeserializer* serializaitionObject)=0;
    //virtual void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject)=0;
};

class XBehaviour : public BotBackend{
    std::vector<InAct<float>> _inputs;
public:
    void insertAction(PlayLayer* playLayer) override;
    void rewindActionQueue(PlayLayer* playLayer) override;
    void reset() override;
    
    const std::vector<InAct<float>>& getInputs(){return _inputs;}

    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

class FrameBehaviour : public BotBackend{
    std::vector<InAct<uint32_t>> _inputs;
public:
    void insertAction(PlayLayer* playLayer) override;
    void rewindActionQueue(PlayLayer* playLayer) override;    
    void reset() override;

    const std::vector<InAct<uint32_t>>& getInputs(){return _inputs;}

    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
