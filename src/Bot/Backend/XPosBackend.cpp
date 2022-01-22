#include "XPosBackend.h"
#include <algorithm>
#include "../Serializer/Serialization.h"
#include "../Deserializer/Deserialization.h"
#include <gd.h>
void XPosBackend::insertCommand(std::unique_ptr<BaseCommand>&& command) {
    float xpos=0; //code to get it from PlayerObject here
    //...
    //...
    _posncom.push_back({xpos, std::move(command)});
}

void XPosBackend::rewindQueue() {
    float currentXPos= gd::PlayLayer::get()->m_pPlayer1->m_position.x;
    auto remIter = std::remove_if(
        std::begin(_posncom), 
        std::end(_posncom),
        [=](const PCPair& pcp){return pcp.first >= currentXPos;}
    );
    _posncom.erase(remIter, _posncom.end());
}

void XPosBackend::reset() {
    _posncom.clear();
}

void XPosBackend::executeCommands() {
    float xpos=gd::PlayLayer::get()->m_pPlayer1->m_position.x;
    while(_posncom[_index].first >= xpos){
        _posncom[_index].second->execute();
        _index++;
    }
}

nlohmann::json XPosBackend::runSerializer(Serializer::BotSerializer* serializaitionObject){
    return serializaitionObject->serialize(this);
}

void XPosBackend::runDeserializer(Deserializer::BotDeserializer* deserializaitionObject){
    deserializaitionObject->deserialize(this);
}
