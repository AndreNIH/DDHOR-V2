#include "Legacy.h"
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <utility>

#include "../Engine.h"

#pragma pack(push, 1)
struct DDHORHeader{
    char magic[4] = {0};
    uint16_t fps;
    uint32_t p1ActionCount;
    uint32_t p2ActionCount;
};
#pragma pack(pop)

template<typename T>
T binaryRead(std::ifstream& ifs){
    T val;
    file.read(reinterpret_cast<char*>(&val), sizeof(T));
    return val;
}

namespace Deserializer
{
    void V1::deserialize(FrameBehaviour* object)
    {
        throw UnsupportedConversion{"V1 DDHOR Files do not support frame based behaviour"};
    }
    
    void V1::deserialize(XBehaviour* object) 
    {
        std::ifstream file(getFilename(), std::ios::binary);
        if(file.is_open()) throw DerError{getFilename() + " not found"};
        DDHORHeader header = binaryRead<DDHORHeader>(file);
        
        int actionCount=0;
        if(object->hasPlayer2Logic()){
            constexpr size_t step = sizeof(float) + sizeof(Action);
            file.seekg(step * header.p1ActionCount, std::ios::beg);
        }
        for(int i=0; i < actionCount; i++){
            float xpos    = binaryRead<float>(file);
            Action action = binaryRead<Action>(file);
            object->insertInputDirectly({xpos, action});
        }
        
    }

    void V1::deserialize(Bot* object){
        std::ifstream file(getFilename(), std::ios::binary);
        if(file.is_open()) throw DerError{getFilename() + " not found"};
        DDHORHeader header;
        file.read(reinterpret_cast<char*>(&header), sizeof(DDHORHeader));
        object->setFPSValue(header.fps);
        object->setMode(BotMode::kXPos);
    }

    
}

