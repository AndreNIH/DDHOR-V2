#pragma once
//
namespace Deserializer{
    class BotDeserializer;
}

using PlayLayer = void;

class BotBehaviour{    
private:

public:
    virtual void insertAction(PlayLayer* playLayer)=0;
    virtual void rewindActionQueue(PlayLayer* playLayer)=0;
    virtual void reset()=0;
    
    //Accept Methods
    //virtual void runSerializer(Deserializer::BotDeserializer* serializaitionObject)=0;
    virtual void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject)=0;
};

class XBehaviour : public BotBehaviour{
    void insertAction(PlayLayer* playLayer) override;
    void rewindActionQueue(PlayLayer* playLayer) override;
    void reset() override{};

    //void runSerializer(Deserializer::BotDeserializer*   serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

class FrameBehaviour : public BotBehaviour{
    void insertAction(PlayLayer* playLayer) override;
    void rewindActionQueue(PlayLayer* playLayer) override;    
    void reset() override{};

    //void runSerializer(Deserializer::BotDeserializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

