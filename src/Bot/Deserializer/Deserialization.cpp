#include "Deserialization.h"
#include <unordered_map>
#include <functional>
#include <spdlog/spdlog.h>

#include "Legacy.h"
#include "V2.h"

namespace Deserializer{
    std::unique_ptr<BotDeserializer> BotDeserializer::create(const std::string& id) 
    {
       using ProductT = std::unique_ptr<BotDeserializer>;
       using CreatorT = std::function<ProductT()>;
       static std::unordered_map<std::string, CreatorT> factory = {
           {"legacy", []()->ProductT {return std::make_unique<Legacy>();}},
           {"v2", []()->ProductT {return std::make_unique<V2>();}},
           {"tasbot", []()->ProductT {return nullptr;}},
           {"xbot", []()->ProductT {return nullptr;}},
           {"ybot", []()->ProductT {return nullptr;}},
           {"zbot", []()->ProductT {return nullptr;}},
       };

       try{
            return factory.at(id)();
       }catch(std::out_of_range& ex){
           spdlog::error("Attempted to create a deserializer object with an invalid id '{}'", id);
           return nullptr;
       }
    }
}
