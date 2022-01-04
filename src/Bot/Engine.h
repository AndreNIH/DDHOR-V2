#pragma once
#include "Behaviour/BotBehavior.h"
#include "Serializer/Serialization.h"
#include "Deserializer/Deserialization.h"
#include <nlohmann/json.hpp>

enum class BotType{};


class FakePlayer{
private:
    BotBehaviour* _behaviour;

public:

    void insertAction(PlayLayer* playLayer){_behaviour->insertAction(playLayer);};
    void rewindActionQueue(PlayLayer* playLayer){_behaviour->rewindActionQueue(playLayer);}
    void reset() {_behaviour->reset();}
    
    void importInputs(Deserializer::BotDeserializer* deserializer);
    nlohmann::json exportInputs(Serializer::BotSerializer* serializer);

};

