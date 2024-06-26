#pragma once
#include <memory>
#include "../Commands/BaseCommand.h"
#include "../Deserializer/Deseriliazble.h"
#include "../Serializer/Serializble.h"
using PlayLayer = void;
class BaseCommand; //fwd declare


enum class BackendPurpose{
    PLAYER_1,
    PLAYER_2,
    COMMAND,
    UNSPECIFIED
};


class CommandBackend : public Deserializable, public Serializable{    
private:
    BackendPurpose _purpose = BackendPurpose::UNSPECIFIED;

public:
    virtual void insertCommand(std::unique_ptr<BaseCommand>&& command)=0;
    virtual void rewindQueue()=0;
    virtual void reset()=0;
    virtual void executeCommands()=0;

    void setPurpose(BackendPurpose purpose){_purpose = purpose;}
    BackendPurpose getPurpose() const{return _purpose;}
    //Accept Methods
    //virtual void runSerializer(Deserializer::BotDeserializer* serializaitionObject)=0;
    //virtual void runDeserializer(Deserializer::BotDeserializer* deserializaitionObject)=0;
};

