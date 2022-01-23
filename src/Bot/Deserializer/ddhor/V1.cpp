#include "V1.h"
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <utility>

#include "../../Engine.h"
#include "../../Backend/XPosBackend.h"
#include "../../Commands/ClickCommands.h"
#include <spdlog/spdlog.h>
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
    ifs.read(reinterpret_cast<char*>(&val), sizeof(T));
    return val;
}

enum class OldAction : char{
    PUSH,
    RELEASE
};

namespace Deserializer
{
    void V1::deserialize(FrameBackend* object)
    {
        throw UnsupportedConversion{"V1 DDHOR Files do not support frame based behaviour"};
    }
    
    void V1::deserialize(XPosBackend* target) 
    {
        std::ifstream file(getFilename(), std::ios::binary);
        if(!file.is_open()) throw DerError{getFilename() + " not found"};
        DDHORHeader header = binaryRead<DDHORHeader>(file);
        
        const bool p2 = target->getPurpose() == BackendPurpose::PLAYER_2;
        int actionCount= p2 ? header.p2ActionCount : header.p1ActionCount;
        if(p2){
            constexpr size_t step = sizeof(float) + sizeof(OldAction);
            file.seekg(step * header.p1ActionCount, std::ios::beg);
        }
        for(int i=0; i < actionCount; i++){
            float xpos    = binaryRead<float>(file);
            OldAction oldAction = binaryRead<OldAction>(file);
            std::unique_ptr<BaseCommand> action = nullptr;            
            if(oldAction==OldAction::PUSH) action = std::make_unique<DoPress>(p2);
            else action = std::make_unique<DoRelease>(p2);
            target->_posncom.push_back({xpos, std::move(action)});
        }        
    }

    void V1::deserialize(Bot* target){
        std::ifstream file(getFilename(), std::ios::binary);
        if(!file.is_open()) throw DerError{getFilename() + " not found"};
        DDHORHeader header;
        file.read(reinterpret_cast<char*>(&header), sizeof(DDHORHeader));
        target->setFPS(header.fps);
        target->setBotBackend(BackendType::XPOS);
        target->_player1._backend->runDeserializer(this);
        target->_player2._backend->runDeserializer(this);
    }

    
}

