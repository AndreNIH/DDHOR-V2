#pragma once
#include "CmdExecuterLogic.h"
#include "../Deserializer/Accessable.h"


class FrameBackend : public CommandBackend{
private:
    EXTEND_DESERIALIZER_ACCESS;
public:
    void insertCommand(std::unique_ptr<BaseCommand>&& command) override;
    void rewindQueue() override;    
    void reset() override;
    void executeCommands() override;
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

class CmdFrameBackend : public FrameBackend{
    EXTEND_DESERIALIZER_ACCESS;
public:
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
