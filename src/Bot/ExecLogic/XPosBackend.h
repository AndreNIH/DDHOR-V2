#pragma once
#include "CmdExecuterLogic.h"

class XPosBackend : public CommandBackend{
public:
    void insertCommand(Command* command) override;
    void rewindQueue() override;
    void reset() override{}
    
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
