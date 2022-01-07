#pragma once
#include <nlohmann/json.hpp>

namespace Serializer{
    class BotSerializer;
}

struct Serializable{
    virtual nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject)=0;
};