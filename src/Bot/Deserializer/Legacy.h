#pragma once
#include "Deserialization.h"
#include "../Behaviour/BotBehavior.h"
namespace Deserializer{
    class V1 : public BotDeserializer{
    public:
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;
        void deserialize(Bot* object) override;
    };

    
}