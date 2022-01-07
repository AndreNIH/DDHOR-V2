#pragma once
#include "Serialization.h"

class XBehaviour;
class FrameBehaviour;
class Bot;

namespace Serializer{
    class V2 : public BotSerializer{
    public:
        nlohmann::json serialize(XBehaviour* object) override;
        nlohmann::json serialize(FrameBehaviour* object) override;
        nlohmann::json serialize(Bot* object) override;
        
    };
}