#pragma once
#include "Deserialization.h"
#include "../Behaviour/BotBehavior.h"
namespace Deserializer{
    
    class Legacy : public BotDeserializer{
    public:
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;
        void Legacy::deserialize(Bot* object) override;
    };

    
}