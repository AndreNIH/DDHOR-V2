#include "Engine.h"
#include "Serializer/V2.h"
#include "Deserializer/V2.h"
#include <spdlog/spdlog.h>

void Bot::importMacro(const std::string& inFilename){
    spdlog::info("Attempting to import macro file: {}", inFilename);
    

}


void Bot::exportMacro(const std::string& outFilename){
    auto ser = std::make_unique<Serializer::V2>();
    auto botJson = runSerializer(ser.get());
    

}


