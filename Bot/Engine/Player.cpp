#include "Player.h"
#include <Hooks/HookManger.h>
#include <stdexcept>


void Player::rewind(float x_pos){
	if(m_actions.empty()) return;
	const size_t initial =  std::clamp(m_actionIndex, static_cast<size_t>(0), m_actions.size()-1);
	for(size_t i = initial; i > 0; i--){
		if(m_actions[i].first < x_pos){
			m_actionIndex = i;
			return;
		}
	}
	m_actionIndex = 0;
	/*auto match = std::find_if(
		m_actions.rbegin(),
		m_actions.rend(),
		[x_pos](auto const& action) {return action.first <= x_pos; }
	);
	if (match == m_actions.rend()) m_actionIndex = 0;
	else m_actionIndex = std::clamp((int)std::distance(match, m_actions.rbegin())-1, 0, (int)m_actions.size());*/
}

void Player::peform(float x_pos){
	//TODO: Add control-switch support
	if (m_actions.empty() || m_actionIndex >= m_actions.size()) return;
	auto act = m_actions[m_actionIndex];
	
	while(m_actionIndex < m_actions.size() && x_pos >= act.first) {
		if (act.second == Act::PUSH) pushButton(m_playLayer, 0, m_player1);
		else releaseButton(m_playLayer, 0, m_player1);
		act = m_actions[++m_actionIndex];
	}
}

bool Player::deserialize(const jsoncons::json& jsonObj){
	m_actions.clear();
	m_actionIndex = 0;
	for (auto& action : jsonObj.array_range()) {
		double pos = action["position"].as_double();
		Act act;
		if (action["action"].as_string() == "PUSH") act = Act::PUSH;
		else if (action["action"].as_string() == "RELEASE") act = Act::RELEASE;
		else return false;

		m_actions.push_back({ pos,act });
	}
	
	return true;
}

Player::Player(bool p1): m_player1(p1) {
	pushButton = HookManager::get().getFunctionPtr<btnFunction>("1b92b7eb72f93e4fcdc80a3930e784961d54f8e7eb49cfb67738f9485b4e6f9d");
	releaseButton = HookManager::get().getFunctionPtr<btnFunction>("cb5a1230ab8154e622c7ba3314c2918add7f6285e5a7324d700553d30af151f1");
	//if (!pushButton || !releaseButton) throw std::runtime_error{ "Critical functions have not been initialized" };
}