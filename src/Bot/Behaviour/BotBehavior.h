#pragma once
#include "../Deserializer/Deseriliazble.h"
#include "../Serializer/Serializble.h"
#include "Actions/Actions.h"

using PlayLayer = void;



class BotBackend : public Deserializable, public Serializable{    
private:
    bool _isPlayer2=false;
public:
    virtual void insertAction(PlayLayer* playLayer)=0;
    virtual void rewindActionQueue(PlayLayer* playLayer)=0;
    virtual void reset()=0;
    
    void setPlayer2Logic() {_isPlayer2 = true;} 
    bool hasPlayer2Logic() {return _isPlayer2;}

    //Accept Methods
    //virtual void runSerializer(Deserializer::BotDeserializer* serializaitionObject)=0;
    //virtual void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject)=0;
};

class XBehaviour : public BotBackend{
    std::vector<InAct<float>> _inputs;
public:
    void insertAction(PlayLayer* playLayer) override;
    void rewindActionQueue(PlayLayer* playLayer) override;
    void reset() override{_inputs.clear();}
    
    const std::vector<InAct<float>>& getInputs(){return _inputs;}
    void insertInputDirectly(const InAct<float>& input){_inputs.push_back(input);}
    
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

class FrameBehaviour : public BotBackend{
    std::vector<InAct<uint32_t>> _inputs;
public:
    void insertAction(PlayLayer* playLayer) override;
    void rewindActionQueue(PlayLayer* playLayer) override;    
    void reset() override {_inputs.clear();}

    const std::vector<InAct<uint32_t>>& getInputs(){return _inputs;}
    void insertInputDirectly(const InAct<uint32_t>& input){_inputs.push_back(input);}

    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
