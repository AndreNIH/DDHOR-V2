#pragma once
#include "CmdExecuterLogic.h"
#include <vector>
<<<<<<< HEAD
=======

#include "../Deserializer/Accessable.h"

>>>>>>> feature/command-migration
class XPosBackend : public CommandBackend{
private:
    using PCPair = std::pair<float, std::unique_ptr<BaseCommand>>;
    std::vector<PCPair> _posAndCommandsContainer;
    size_t _index;
<<<<<<< HEAD
public:
    void insertCommand(std::unique_ptr<BaseCommand>&& command) override;
    void rewindQueue() override;
    void reset() override{}
=======
    EXTEND_DESERIALIZER_ACCESS;
public:
    void insertCommand(std::unique_ptr<BaseCommand>&& command) override;
    void rewindQueue() override;
    void reset() override;
>>>>>>> feature/command-migration
    void executeCommands() override;

    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
<<<<<<< HEAD
=======

class CmdXPosBackend : public XPosBackend{
    EXTEND_DESERIALIZER_ACCESS;
public:
    nlohmann::json runSerializer(Serializer::BotSerializer* serializaitionObject) override;
    void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject) override;
};
>>>>>>> feature/command-migration
