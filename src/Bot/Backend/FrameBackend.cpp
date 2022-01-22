#include "FrameBackend.h"
#include "../Serializer/Serialization.h"
#include "../Deserializer/Deserialization.h"
void FrameBackend::insertCommand(std::unique_ptr<BaseCommand>&& command){
    int frame = 0; //get it from playlayer;
    _posncom.push_back({frame, std::move(command)});
}

void FrameBackend::rewindQueue(){
    //implement later
}

void FrameBackend::rollbackQueue(){

}

void FrameBackend::reset(){

}
void FrameBackend::executeCommands(){

}

nlohmann::json FrameBackend::runSerializer(Serializer::BotSerializer* serializaitionObject){
    return serializaitionObject->serialize(this);
}
void FrameBackend::runDeserializer(Deserializer::BotDeserializer* deserializaitionObject){
    deserializaitionObject->deserialize(this);
}