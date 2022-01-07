#pragma once

namespace Deserializer{
    class BotDeserializer;
}

struct Deserializable{
    virtual void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject)=0;
};