#include "LegacyDDHOR.h"

namespace Legacy{
    bool isDDHROld(std::ifstream& ifs){
        ifs.seekg(0, std::ios::beg);
        char sig[4] = {0};
        ifs.read(&sig[0],4);
        bool isOld = std::memcmp(sig,"DDHR",4) == 0;
        ifs.clear();
        ifs.seekg(0, std::ios::beg);
        return isOld;
    }

    DDHORHeader parseHeader(std::ifstream& ifs){
         DDHORHeader header;
         ifs.read(reinterpret_cast<char*>(&header), sizeof(DDHORHeader));
         return header;
    }

    std::vector<PlayerAction> parsePlayerInput(std::ifstream& ifs, size_t count){
        std::vector<PlayerAction> actions;
        actions.reserve(count);
        for(int i=0; i < count; i++){
            float xpos = 0;
            Actions action;
            ifs.read(reinterpret_cast<char*>(&xpos), sizeof(float));
            ifs.read(reinterpret_cast<char*>(&action), sizeof(Actions));
            actions.push_back({xpos,action});
        }
        return actions;
    }
}