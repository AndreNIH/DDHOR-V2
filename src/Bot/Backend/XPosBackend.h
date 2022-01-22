#pragma once
#include "CmdExecuterLogic.h"
#include <vector>

#include "../Deserializer/Accessable.h"

class XPosBackend : public CommandBackend{
private:
    using PCPair = std::pair<float, std::unique_ptr<BaseCommand>>;
    std::vector<PCPair> _posncom; //Position & Command
    size_t _index;
    EXTEND_DESERIALIZER_ACCESS;
public:
    void insertCommand(std::unique_ptr<BaseCommand>&& command) override;
    void rewindQueue() override;
    void reset() override;
    void executeCommands() override;

    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

class CmdXPosBackend : public XPosBackend{
    EXTEND_DESERIALIZER_ACCESS;
public:
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
