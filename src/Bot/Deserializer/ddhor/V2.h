#pragma once
#include "../Deserialization.h"
#include <optional>
#include <nlohmann/json.hpp>

class XPosBackend;
class FrameBackend;
class Bot;

namespace Deserializer{
    
    class V2 : public BotDeserializer{
    private:
        std::optional<nlohmann::json> _bufferedJSON;
        nlohmann::json& getBufferedJSON();
    public:
        void deserialize(XPosBackend* object) override;
        void deserialize(FrameBackend* object) override;
        void deserialize(CmdXPosBackend* target) override;
        void deserialize(CmdFrameBackend* object) override;
        void deserialize(Bot* object) override;
    };
    
}