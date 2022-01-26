#include "V2.h"
#include <fstream>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "jsonSpecialization.h"
#include "../../Backend/CmdExecuterLogic.h"
#include "../../Backend/XPosBackend.h"
#include "../../Backend/FrameBackend.h"
#include "../../Engine.h"
#include "../../Commands/ClickCommands.h"
#include <ErrorHandling/DExceptions.h>

std::unique_ptr<BaseCommand> createPlayerInputCommand(const std::string& id, bool p2){
    std::unique_ptr<BaseCommand> command = nullptr;
    if(id == "PUSH") command = std::make_unique<DoPress>(p2);
    else if(id == "RELEASE") command = std::make_unique<DoRelease>(p2);
    return command;
}


namespace Deserializer
{
    
    nlohmann::json& V2::getBufferedJSON() 
    {
        if(!_bufferedJSON.has_value()){
            try{
                std::ifstream file(this->getFilename());
                if(!file.is_open()) throw DEX::FileNotFound{getFilename() + " not found"};
                nlohmann::json object;
                file >> object;
                _bufferedJSON = object;
            }catch(nlohmann::json::exception& ex){
                throw DEX::DeserializerError(ex.what());
            }
        }
        return _bufferedJSON.value();
    }

    
    
    
    void V2::deserialize(FrameBackend* target)
    {
        nlohmann::json data = getBufferedJSON();
        const bool isP2 = target->getPurpose() == BackendPurpose::PLAYER_2;
        nlohmann::json player = isP2 ? data.at("inputsP2") : data.at("inputsP1");
        for(auto& input : player){
            const int pos = input.at("position");
            const std::string action = input.at("action");
            std::unique_ptr<BaseCommand> command = createPlayerInputCommand(action, isP2);
            if(command == nullptr) throw DEX::DeserializerError{fmt::format("Unrecognized command: {}", action)};
            target->_posncom.push_back({pos, std::move(command)});
        }
    }
    
    void V2::deserialize(XPosBackend* target) 
    {
        nlohmann::json data = getBufferedJSON();
        const bool isP2 = target->getPurpose() == BackendPurpose::PLAYER_2;
        nlohmann::json player = isP2 ? data.at("inputsP2") : data.at("inputsP1");
        for(auto& input : player){
            const float pos = input.at("position");
            const std::string action = input.at("action");
            std::unique_ptr<BaseCommand> command = createPlayerInputCommand(action, isP2);
            if(command == nullptr) throw DEX::DeserializerError{fmt::format("Unrecognized command: {}", action)};
            target->_posncom.push_back({pos, std::move(command)});
        }
    }    


    void V2::deserialize(CmdFrameBackend* target){
        throw DEX::IllegalOperation{"Not yet implemented, flag1"};
    }
   
    void V2::deserialize(CmdXPosBackend* target){
        throw DEX::IllegalOperation{"Not yet implemented, flag2"};
    }
    
    void V2::deserialize(Bot* target){
        try{
            auto data = getBufferedJSON();
            target->setFPS(data.at("fps"));
            target->setBotBackend(data.at("macro"));
            target->_player1._backend->runDeserializer(this);
            target->_player2._backend->runDeserializer(this);
        }catch(const nlohmann::json::exception& ex){
            throw DEX::DeserializerError{ex.what()};
        }
    }
}

