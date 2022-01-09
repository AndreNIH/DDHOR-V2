#include "V2.h"
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "../Behaviour/BotBehavior.h"
#include "../Behaviour/Actions/Actions.h"
#include "../Engine.h"


namespace Deserializer
{
    
    nlohmann::json& V2::getBufferedJSON() 
    {
        if(!_bufferedJSON.has_value()){
            try{
                std::ifstream file(this->getFilename());
                if(!file.is_open()) throw DerError{getFilename() + " not found"};
                nlohmann::json object;
                file >> object;
                _bufferedJSON = object;
            }catch(nlohmann::json::exception& ex){
                throw DerError(ex.what());
            }
        }
        return _bufferedJSON.value();
    }

    
    
    
    void V2::deserialize(FrameBehaviour* object)
    {
        try{
            auto deserializedObj = getBufferedJSON();
            auto player = object->hasPlayer2Logic()
                ? deserializedObj.at("inputsP1")
                : deserializedObj.at("inputsP2");
            
            for(auto& input :player){
                unsigned int pos = input.at("position");
                Action action = ActionTools::strAsAction(input.at("action"));
                object->insertInput({pos,action});
            }

        }catch(nlohmann::json::exception& ex){
            throw DerError(ex.what());
        }
    }
    
    void V2::deserialize(XBehaviour* object) 
    {
        try{
            auto deserializedObj = getBufferedJSON();
            auto player = object->hasPlayer2Logic()
                ? deserializedObj.at("inputsP2")
                : deserializedObj.at("inputsP1");
            
            for(auto& input : player){
                float pos = input.at("position");
                Action action = ActionTools::strAsAction(input.at("action"));
                object->insertInput({pos,action});
            }

        }catch(nlohmann::json::exception& ex){
            throw DerError(ex.what());
        }
    }

    void V2::deserialize(Bot* object)
    {
        try{
            auto deserializedObj = getBufferedJSON();
            object->setFPSValue(deserializedObj.at("fps"));
            if(deserializedObj.at("macro") == "x-position") object->setMode(BotMode::kXPos);
            else if(deserializedObj.at("macro") == "frames") object->setMode(BotMode::kFrames);
            else throw DerError{"Invalid argument passed at 'mode' field: {} is not a valid argument"};
        }catch(nlohmann::json::exception& ex){
            throw DerError(ex.what());
        }
    }
}

