#include "XPosBackend.h"
#include <gd.h>
#include <algorithm>
#include "../Serializer/Serialization.h"
#include "../Deserializer/Deserialization.h"
#include <spdlog/spdlog.h>

//Dirty trick
#pragma pack(push, 1)
	class PlayerObject
	{
	public:
		char pad_0000[32]; //0x0000
		float xRotation; //0x0020
		float yRotation; //0x0024
		char pad_0028[1494]; //0x0028
		bool orbFix; //0x05FE
		char pad_05FF[41]; //0x05FF
		double yVelocityVec; //0x0628
		char pad_0630[8]; //0x0630
		bool shipMode; //0x0638
		char pad_0639[6]; //0x0639
		bool isDead; //0x063F
		char pad_0640[60]; //0x0640
		float XPos; //0x067C
		float YPos; //0x0680
	}; //Size: 0x0684
	static_assert(sizeof(PlayerObject) == 0x684);
	static_assert(sizeof(PlayerObject) == 0x684);
	#pragma pack(pop)

void XPosBackend::insertCommand(std::unique_ptr<BaseCommand>&& command) {
    spdlog::info("XPosBackend::insertCommand");
    float xpos=gd::PlayLayer::get()->m_pPlayer1->m_position.x;
    _posncom.push_back({xpos, std::move(command)});
}

void XPosBackend::rewindQueue() {
    spdlog::info("XPosBackend::rewindQueue");
    float currentXPos= gd::PlayLayer::get()->m_pPlayer1->m_position.x;    
    while(_index && currentXPos > _posncom[_index].first){
        if(--_index < 0){
            _index=0;
            return;
        }
    }
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
    float xpos=reinterpret_cast<PlayerObject*>(gd::PlayLayer::get()->m_pPlayer1)->XPos;
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
