#include "XPosBackend.h"
#include <gd.h>
#include <algorithm>
#include "../Serializer/Serialization.h"
#include "../Deserializer/Deserialization.h"
#include <spdlog/spdlog.h>



void XPosBackend::insertCommand(std::unique_ptr<BaseCommand>&& command) {
    spdlog::info("XPosBackend::insertCommand");
    float xpos=gd::PlayLayer::get()->m_pPlayer1->m_position.x;
    _posncom.push_back({xpos, std::move(command)});
}

void XPosBackend::rewindQueue() {
    spdlog::info("XPosBackend::rewindQueue");
    float currentXPos= gd::PlayLayer::get()->m_pPlayer1->m_position.x;    
    if(_index == _posncom.size()) _index=0;
    while(_index && currentXPos < _posncom[_index].first) _index--;
}

void XPosBackend::rollbackQueue() {
    spdlog::info("XPosBackend::rollbackQueue");
    float currentXPos= gd::PlayLayer::get()->m_pPlayer1->m_position.x;
    auto remIter = std::remove_if(
        std::begin(_posncom), 
        std::end(_posncom),
        [=](const PCPair& pcp){return pcp.first >= currentXPos;}
    );
    _posncom.erase(remIter, _posncom.end());
}

void XPosBackend::reset() {
    spdlog::info("XPosBackend::reset");
    _posncom.clear();
}

void XPosBackend::executeCommands() {
    float xpos= gd::PlayLayer::get()->m_pPlayer1->m_position.x;
    while(_index < _posncom.size() && xpos >= _posncom[_index].first){
        spdlog::info("XPosBackend::executeCommand, current position is '{}', next command runs on", xpos, _posncom[_index].first);
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
