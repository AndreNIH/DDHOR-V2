#pragma once
#include <fstream>
#include <vector>
namespace Legacy{
    enum class Actions : char {
        HOLD,
        RELEASE
    };

    struct PlayerAction {
        float xposition;
        Actions action;
    };
    
    #pragma pack(push, 1)
    struct DDHORHeader{
        char magic[4] = {0};
        uint16_t fps;
		uint32_t p1ActionCount;
		uint32_t p2ActionCount;
    };
    #pragma pack(pop)

    bool isDDHROld(std::ifstream& ifs);
    
    DDHORHeader parseHeader(std::ifstream& ifs);
    std::vector<PlayerAction> parsePlayerInput(std::ifstream& ifs, size_t count);
    
}