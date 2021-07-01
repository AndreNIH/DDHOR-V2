#include "Recorder.h"

JSONCONS_ENUM_TRAITS(Act, PUSH, RELEASE);

bool Recorder::isDuplicate(const Action& action){
	return std::find_if(
		m_actions.cbegin(),
		m_actions.cend(),
		[action](const auto& evaluatedAction) {
			auto [pos1, act1] = action;
			auto [pos2, act2] = evaluatedAction;
			return (pos1 == pos2) && (act1 == act2);
		}) != m_actions.cend();
}

void Recorder::rollback(float x_pos){
	m_actions.erase(std::remove_if(
		m_actions.begin(),
		m_actions.end(),
		[x_pos](const auto& action) {return action.first >= x_pos; }
	), m_actions.end());

}

void Recorder::addInput(float x_pos, Act action){
	//if (x_pos <= 0 || isDuplicate({ x_pos,action })) return;
	//if (x_pos <= 0) return;
	m_actions.push_back({ x_pos, action });
}

std::optional<Act> Recorder::lastAction(){
	if (m_actions.empty()) return std::nullopt;
	return m_actions.back().second;
}

jsoncons::json Recorder::serialize(){
	using namespace jsoncons;
	json jsonObj(json_array_arg);
	for (auto& [pos, act] : m_actions) {
		json arr;
		arr.insert_or_assign("position", pos);
		arr.insert_or_assign("action", act);
		jsonObj.push_back(std::move(arr));
	}
	m_actions.clear();
	return jsonObj;
}
		
