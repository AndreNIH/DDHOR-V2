#include "Validator.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "json/FastJSONValidator.h"

#define TRUE_OR_RETF(condition) if(!condition) return false;


namespace Validators{
    
    //=========================================================================
    // DDHOR-BOT
    //=========================================================================
    
    bool isDDHORV1(const std::string& filename){
        std::ifstream file(filename, std::ios::binary);
        if(!file.is_open()) return false;
        char sig[5] = {0};
        file.read(&sig[0], 4);
        return strcmp(sig,"DDHR") == 0;
    }

    bool isDDHORV2(const std::string& filename){
        JSONLazyValidator validator;
        validator.setQualifierPattern("{[");
        validator.setStringCorrection("]}");
        validator.setValidator(
            [](const std::string jstring)->bool{
                spdlog::info(jstring);
                auto object = nlohmann::json::parse(jstring);
                TRUE_OR_RETF(object.contains("fps"));
                TRUE_OR_RETF(object.contains("inputsP1"));
                //TRUE_OR_RETF(object.at("inputsP1").contains("action"));
                //TRUE_OR_RETF(object.at("inputsP1").contains("position"));
                return true;
            }
        );
        return validator.validateFile(filename);
    }

    //=========================================================================
    // TAS-BOT
    //=========================================================================
    
    bool isTASBOT1(const std::string& filename){
        
        return false;
        
    }

    bool isTASBOT2(const std::string& filename){
        JSONLazyValidator validator;
        validator.setQualifierPattern("{[{{}");
        validator.setStringCorrection("}]}");
        validator.setValidator(
             [](const std::string jstring)->bool{
                auto object = nlohmann::json::parse(jstring);
                TRUE_OR_RETF(object.contains("fps"));
                auto macro = object.at("macro");
                TRUE_OR_RETF(macro.contains("frame"));
                TRUE_OR_RETF(macro.contains("player_1"));
                TRUE_OR_RETF(macro.contains("click"));
                TRUE_OR_RETF(macro.contains("x_position"));
                return true;
             }
        );
        return validator.validateFile(filename);
        
    }
    //=========================================================================
    // Z-BOT
    //=========================================================================
    bool isZBOT(const std::string& filename){
        
        return false;
        
    }

    bool isZBOTF(const std::string& filename){
        
        return false;
        
    }
    //=========================================================================
    // Y-BOT
    //=========================================================================

    bool isYBOT(const std::string& filename){
        
        return false;
        
    }
    
    //=========================================================================
    // REPLAY-BOT
    //=========================================================================

}