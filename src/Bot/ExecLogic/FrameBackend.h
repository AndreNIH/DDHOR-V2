#pragma once
#include "CmdExecuterLogic.h"
#include "../Deserializer/Accessable.h"


class FrameBackend : public CommandBackend{
private:
    EXTEND_DESERIALIZER_ACCESS;
    using PCPair = std::pair<unsigned int, std::unique_ptr<BaseCommand>>;
    std::vector<PCPair> _posncom;
    size_t _index=0;
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
