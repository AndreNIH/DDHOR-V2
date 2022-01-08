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

    std::string getFactoryId() const {return _factoryId;}
};

std::unique_ptr<Deserializer::BotDeserializer> getCompatibleDeserializer(const std::string file){
    using Cont = std::vector<Creator>;
    static std::unordered_map<std::string, Cont> mappings
    {
            {".ddhor", {
                Creator("v1", Validators::isDDHORV1), 
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
        spdlog::info("Requesting a deserializer for {}", file);
        for(auto& creator : creatorList->second){
            spdlog::info("Matching the {} file with a '{}' deserializer", ext, creator.getFactoryId());
            auto der = creator.createIfValid(file);
            if(der != nullptr) {
                der->setFilename(file);
                return der;
            }
        }   
    }else{
        spdlog::warn(" Could not find any registed deserializers which match a {} file", ext);
    }
    spdlog::warn("Failed to obtain a deserializer for {}", file);
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