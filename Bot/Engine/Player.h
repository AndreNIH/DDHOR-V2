#pragma once
#include "../GDTypes/PlayLayer.h"
#include <vector>
#include "BotActions.h"
#include <jsoncons/json.hpp>
class Player {
private:
	

	GT::PlayLayer* m_playLayer = nullptr;
	const bool m_player1;
	
	std::vector<Action>m_actions;
	size_t m_actionIndex = 0;

	typedef void(__thiscall* btnFunction)(void*, int a1, bool leftTocuh);
	btnFunction pushButton    = nullptr;
	btnFunction releaseButton = nullptr;


public:
	void rewind(float x_pos);
	void peform(float x_pos);
	void bindObject(GT::PlayLayer* playLayer) {m_playLayer = playLayer;};
	
	bool deserialize(const jsoncons::json& jsonObj);

	Player(bool p1);
};