#pragma once
#include "Deserialization.h"


class XBehaviour;
class FrameBehaviour;
class Bot;

namespace Deserializer{
    
    class V2 : public BotDeserializer{
    public:
        void deserialize(XBehaviour* object) override;
        void deserialize(FrameBehaviour* object) override;
        void deserialize(Bot* object) override;
    };
    
}