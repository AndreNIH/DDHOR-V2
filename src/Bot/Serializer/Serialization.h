#pragma once
#include <nlohmann/json.hpp>


class XPosBackend;
class FrameBackend;
class Bot;

namespace Serializer{
    
    class BotSerializer{
    public:
        virtual nlohmann::json serialize(XPosBackend* object)=0;
        virtual nlohmann::json serialize(FrameBackend* object)=0;
        virtual nlohmann::json serialize(Bot* object)=0;
    };




}