#include "V2.h"
#include "../Behaviour/BotBehavior.h"
#include "../Engine.h"
#include <iostream>
#include <spdlog/spdlog.h>

using namespace nlohmann;

namespace Serializer
{
    nlohmann::json V2::serialize(XBehaviour* object)
    {
        
        spdlog::info("Serializing a {} object, using {} serializer object", 
                    typeid(object).name(), 
                    typeid(this).name());

        json serializedPlayer;
        for(auto& input : object->getInputs()){
            serializedPlayer.push_back({
                {"position", input.location},
                {"action", ActionTools::actionAsStr(input.action)}
            });
        }
        return serializedPlayer;
    }
    
    nlohmann::json V2::serialize(FrameBehaviour* object)
    {
        spdlog::info("Serializing a {} object, using {} serializer object", 
                    typeid(object).name(), 
                    typeid(this).name());
        
        json serializedPlayer;
        for(auto& input : object->getInputs()){
            serializedPlayer.push_back({
                {"frame", input.location},
                {"action", ActionTools::actionAsStr(input.action)}
            });
        }
        return serializedPlayer;
    }
    
    nlohmann::json V2::serialize(Bot* object) 
    {
        spdlog::info("Serializing a {} object, using {} serializer object", 
                    typeid(object).name(), 
                    typeid(this).name());
        
        json serializedObj;
        serializedObj["version"] = "2.0";
        serializedObj["levelID"] = nullptr;
        serializedObj["fps"] = object->getFPSValue();
        serializedObj["macro"] = object->getMode() == BotMode::kXPos ? "x-position" : "frames";
        serializedObj["inputsP1"] = object->player().first.runSerializer(this);
        serializedObj["inputsP2"] = object->player().second.runSerializer(this);

        return serializedObj;
    }
}