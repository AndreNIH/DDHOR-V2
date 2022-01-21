#pragma once
#include "CmdExecuterLogic.h"
<<<<<<< HEAD



class FrameBackend : public CommandBackend{
=======
#include "../Deserializer/Accessable.h"


class FrameBackend : public CommandBackend{
private:
    EXTEND_DESERIALIZER_ACCESS;
    using PCPair = std::pair<unsigned int, std::unique_ptr<BaseCommand>>;
    std::vector<PCPair> _posncom;
    size_t _index=0;
>>>>>>> feature/command-migration
public:
    void insertCommand(std::unique_ptr<BaseCommand>&& command) override;
    void rewindQueue() override;    
    void reset() override;
    void executeCommands() override;
<<<<<<< HEAD
    
=======
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};

class CmdFrameBackend : public FrameBackend{
    EXTEND_DESERIALIZER_ACCESS;
public:
>>>>>>> feature/command-migration
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
