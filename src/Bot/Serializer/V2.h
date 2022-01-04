#pragma once
#include "Serialization.h"

class XBehaviour;
class FrameBehaviour;

namespace Serializer{
    class V2 : public BotSerializer{
        void serialize(XBehaviour* object) override;
        void serialize(FrameBehaviour* object) override;
    };
}