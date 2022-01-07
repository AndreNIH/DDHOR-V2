//Bot Deserializer Iterator
#include <string>
#include <functional>
#include <filesystem>
#include "Validator.h"
#include  <spdlog/spdlog.h>
#include "../Deserializer/Deserialization.h"

class Creator{
private:
    using VerifierProto = bool(const std::string&);
    const std::function<VerifierProto> _validator;
    const std::string _factoryId;
public:
    Creator(const std::string& id, const std::function<VerifierProto>& validator) :
        _validator(validator),
        _factoryId(id) {} 

    std::unique_ptr<Deserializer::BotDeserializer> createIfValid(const std::string& filename){
        if(_validator(filename)){
            return Deserializer::BotDeserializer::create(_factoryId);
        }
        return nullptr;
    } 
};

std::unique_ptr<Deserializer::BotDeserializer> getCompatibleDeserializer(const std::string file){
    using Cont = std::vector<Creator>;
    static std::unordered_map<std::string, Cont> mappings
    {
            {".ddhor", {
                Creator("legacy", Validators::isLegacyDDHOR), 
                Creator("v2", Validators::isDDHORV2)
            }},

            {".json", {
                Creator("tasbot1", Validators::isTASBOT1),
                Creator("tasbot2", Validators::isTASBOT2)
            }}
    };

    const std::string ext = std::filesystem::path(file).extension().string();    
    auto creatorList = mappings.find(ext);
    
    if(creatorList != std::end(mappings)){
        for(auto& creator : creatorList->second){
            auto der = creator.createIfValid(file);
            if(der != nullptr) return der;
        }   
    }
    spdlog::warn("Failed to obtain a deserializer for {}.Could not find any deserializers which match a {}  file", file ,ext);
    return nullptr;
}



  

/*void* deduceType(file){
    map<string, deserializerIter> mapping{
        {".ddhor", Creator(v2, verif) | Creat},
        {".zbot", zbot},
        {".ybot", ybot},
        {".json", tasbot}
    } 

    Iterator it  = mapping.at(file.extension);
    for(it )
    try{

    }catch(FormatError& e){

    }

}*/