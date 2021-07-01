#include "Manager.h"
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include "Engine/internal/LegacyDDHOR.h"

using std::filesystem::exists;
unipair<Recorder>& Bot::recorder()
{
	if (m_state != State::Recording)
		throw std::runtime_error{ "Illegal access: Bot is not recording" };
	return m_recorders;
}

unipair<Player>& Bot::player()
{
	if (m_state != State::Playing)
		throw std::runtime_error{ "Illegal access: Bot is not playing" };
	return m_players;
}

void Bot::bindObject(GT::PlayLayer* layer) {
	m_players.first.bindObject(layer);
	m_players.second.bindObject(layer);
}

Bot& Bot::get() {
	static Bot instance ;
	return instance;
}

SERDERR Bot::serialize(std::string const& filename) {
	using namespace jsoncons;
	std::ofstream ofs("ddhor/"+filename);
	if (!ofs.is_open()) return SERDERR::FileNotFound;

	try {
		json jsonObj;
		jsonObj["levelID"] = json::null();
		jsonObj["macro"] = "x-position";
		jsonObj["fps"] = m_botConfig.getFPS();
		jsonObj["inputsP1"] = std::move(m_recorders.first.serialize());
		jsonObj["inputsP2"] = std::move(m_recorders.second.serialize());
		jsonObj.dump_pretty(ofs);

	}
	catch (jsoncons::key_not_found& e) {
		return SERDERR::SerErr;
	}
	return SERDERR::Ok;
}


using namespace jsoncons;
	
json binActionsToJSON(const std::vector<Legacy::PlayerAction>& vec){
	json actionsArrayObj(json_array_arg);
	for(auto& e : vec){
		std::string act = e.action == Legacy::Actions::HOLD ? "PUSH" : "RELEASE";
		json actionObj(json_object_arg, {
			{"position", e.xposition},
			{"action" ,act}
		});
		actionsArrayObj.push_back(std::move(actionObj));
	}
	return actionsArrayObj;
}

json generateJSON(const std::string& path){
	json obj;
	std::ifstream file(path, std::ios::binary);
	if(Legacy::isDDHROld(file)){
		auto header = Legacy::parseHeader(file);
		auto p1bin = Legacy::parsePlayerInput(file,header.p1ActionCount);
		auto p2bin = Legacy::parsePlayerInput(file,header.p2ActionCount);
		obj["levelID"] = json::null();
		obj["fps"] = header.fps;
		obj["macro"] = "x-position";
		obj["inputsP1"] = std::move(binActionsToJSON(p1bin));
		obj["inputsP2"] = std::move(binActionsToJSON(p2bin));
	}else{
		file.close();
		file.open(path);
		obj = json::parse(file);
	}
	return obj;
}

SERDERR Bot::deserialize(std::string const& filename) {
	
	const std::string macroPath = "ddhor/" + filename;
	if (!std::filesystem::exists(macroPath)) return SERDERR::FileNotFound;

	try {
		json jsonObj = generateJSON(macroPath);  
		m_botConfig.setFPS(jsonObj["fps"].as_double());
		m_players.first.deserialize(jsonObj["inputsP1"]);
		m_players.second.deserialize(jsonObj["inputsP2"]);
	}
	catch (jsoncons::key_not_found& e) {
		return SERDERR::DerErr;
	}
	catch (jsoncons::ser_error& e) {
		return SERDERR::DerErr;
	}
	return SERDERR::Ok;
}