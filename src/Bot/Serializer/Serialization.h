#pragma once
#include <nlohmann/json.hpp>


class XBehaviour;
class FrameBehaviour;
class Bot;

namespace Serializer{
    
    class BotSerializer{
    public:
        virtual nlohmann::json serialize(XBehaviour* object)=0;
        virtual nlohmann::json serialize(FrameBehaviour* object)=0;
        virtual nlohmann::json serialize(Bot* object)=0;
    };




}