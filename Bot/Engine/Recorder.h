#pragma once
#include "../GDTypes/PlayLayer.h"
#include <optional>
#include <vector>
#include <jsoncons/json.hpp>
#include "BotActions.h"

class Recorder {
private:
	std::vector<Action>m_actions;
	bool isDuplicate(const Action& action);
public:
	void rollback(float x_pos);
	void addInput(float x_pos, Act action);
	std::optional<Act>lastAction();

	jsoncons::json serialize();

};