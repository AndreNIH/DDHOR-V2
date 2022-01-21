#pragma once
#include "../Deserialization.h"

class XPosBackend;
class FrameBackend;
class Bot;

namespace Deserializer{
    class V1 : public BotDeserializer{
    public:
        void deserialize(XPosBackend* object) override;
        void deserialize(FrameBackend* object) override;
        void deserialize(Bot* object) override;
    };

    
}