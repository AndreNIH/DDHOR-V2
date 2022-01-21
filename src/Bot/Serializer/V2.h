#pragma once
#include "Serialization.h"

class XPosBackend;
class FrameBackend;
class Bot;

namespace Serializer{
    class V2 : public BotSerializer{
    public:
        nlohmann::json serialize(XPosBackend* object) override;
        nlohmann::json serialize(FrameBackend* object) override;
        nlohmann::json serialize(Bot* object) override;
        
    };
}