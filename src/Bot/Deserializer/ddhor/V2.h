#pragma once
#include "Deserialization.h"
#include <optional>
#include <nlohmann/json.hpp>

class XBehaviour;
class FrameBehaviour;
class Bot;

namespace Deserializer{
    
    class V2 : public BotDeserializer{
    private:
        std::optional<nlohmann::json> _bufferedJSON;
        nlohmann::json& getBufferedJSON();
    public:
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;
        void deserialize(Bot* object) override;
    };
    
}