#pragma once
#include "../Deserializer/Deseriliazble.h"
#include "../Serializer/Serializble.h"
#include "Actions/Actions.h"

using PlayLayer = void;

//Bot-Position Storage
template<typename T>
class BPStorage{
protected:
    std::vector<IAS<T>> _inputsContainer;
public:
    const std::vector<IAS<T>>& getInputs() const{return _inputContainer};
    void insertInput(const IAS<T>& input) {_inputsContainer.push_back(input);}
};

class BotBackend : public Deserializable, public Serializable{    
private:
    bool _isPlayer2=false;
public:
    virtual void insertAction(Action action)=0;
    virtual void rewindActionQueue(PlayLayer* playLayer)=0;
    virtual void reset()=0;
    virtual void perform();

    void setPlayer2Logic() {_isPlayer2 = true;} 
    bool hasPlayer2Logic() {return _isPlayer2;}

    //Accept Methods
    //virtual void runSerializer(Deserializer::BotDeserializer* serializaitionObject)=0;
    //virtual void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject)=0;
};

class XBehaviour : public BotBackend, public BPStorage<float>{
public:
    void insertAction(Action action) override;
    void rewindActionQueue(PlayLayer* playLayer) override;
    void reset() override{_inputsContainer.clear();}
    
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

class FrameBehaviour : public BotBackend, public BPStorage<int>{
public:
    void insertAction(Action action) override;
    void rewindActionQueue(PlayLayer* playLayer) override;    
    void reset() override {_inputsContainer.clear();}

    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
