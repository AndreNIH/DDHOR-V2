#include "XPosBackend.h"
#include <algorithm>

void XPosBackend::insertCommand(std::unique_ptr<BaseCommand>&& command) {
    float xpos=0; //code to get it from PlayerObject here
    //...
    //...
    _posAndCommandsContainer.push_back({xpos, std::move(command)});
}

void XPosBackend::rewindQueue() {
    float currentXPos=0; //code to get it from PlayerObject here
    auto remIter = std::remove_if(
        std::begin(_posAndCommandsContainer), 
        std::end(_posAndCommandsContainer),
        [=](const PCPair& pcp){return pcp.first >= currentXPos;}
    );
}

void XPosBackend::reset() {

}

void XPosBackend::executeCommands() {
    float xpos;
    if(_posAndCommandsContainer[_index].first == xpos){
        _posAndCommandsContainer[_index].second->execute();
    }
}
