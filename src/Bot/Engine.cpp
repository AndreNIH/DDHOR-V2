#include "Engine.h"
#include "Serializer/V2.h"
#include "Deserializer/V2.h"
#include <spdlog/spdlog.h>
#include "Deductor/DerDeductor.h"

void Bot::importMacro(const std::string& inFilename){
    spdlog::info("Attempting to import macro file: {}", inFilename);
    auto deserializer = getCompatibleDeserializer(inFilename);
    if(deserializer == nullptr){
       //do nothing for the moment being
    }
    this->runDeserializer(deserializer.get());
    _player1->runDeserializer(deserializer.get());
    _player2->runDeserializer(deserializer.get());
    

}


void Bot::exportMacro(const std::string& outFilename){
    auto ser = std::make_unique<Serializer::V2>();
    auto botJson = runSerializer(ser.get());
    

}


