#include "Deserialization.h"
#include <unordered_map>
#include <functional>
#include <spdlog/spdlog.h>
#include <typeinfo>
#include "ddhor/V1.h"
#include "ddhor/V2.h"
#include <ErrorHandling/DExceptions.h>

namespace Deserializer{
    std::unique_ptr<BotDeserializer> BotDeserializer::create(const std::string& id) 
    {
       using ProductT = std::unique_ptr<BotDeserializer>;
       using CreatorT = std::function<ProductT()>;
       static std::unordered_map<std::string, CreatorT> factory = {
           {"v1", []()->ProductT {return std::make_unique<V1>();}},
           {"v2", []()->ProductT {return std::make_unique<V2>();}},
           {"tasbot", []()->ProductT {return nullptr;}},
           {"xbot", []()->ProductT {return nullptr;}},
           {"ybot", []()->ProductT {return nullptr;}},
           {"zbot", []()->ProductT {return nullptr;}},
       };

       try{
            auto obj = factory.at(id)();
            spdlog::info("Succesfully created an object with ID '{}'", id);
            return obj;
       }catch(std::out_of_range& ex){
           spdlog::error("Attempted to create a deserializer object with an invalid ID '{}'", id);
           return nullptr;
       }
    }

    void BotDeserializer::deserialize(CmdXPosBackend* object){
        const auto msg = fmt::format("{} deserializer does not support {} objects", 
            typeid(this).name(), 
            typeid(object).name());
        throw DEX::IllegalOperation{msg};
    }

    void BotDeserializer::deserialize(CmdFrameBackend* object){
        const auto msg = fmt::format("{} deserializer does not support {} objects", 
            typeid(this).name(), 
            typeid(object).name());
        throw DEX::IllegalOperation{msg};
    }


}
