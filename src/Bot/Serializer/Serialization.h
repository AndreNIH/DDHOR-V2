#pragma once


class XBehaviour;
class FrameBehaviour;

using ReturnT = void; //Placeholder type

namespace Serializer{
    
    class BotSerializer{
    public:
        virtual void serialize(XBehaviour* object)=0;
        virtual void serialize(FrameBehaviour* object)=0;
    };

}