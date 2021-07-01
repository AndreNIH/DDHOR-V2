#pragma once
#include "Recorder.h"
#include "Player.h"
#include "Config.h"
#include "../GDTypes/PlayLayer.h"
#include <utility>



template<class T>
using unipair = std::pair<T, T>;

enum class SERDERR {
	FileExists,
	FileNotFound,
	SerErr,
	DerErr,
	Ok
};

class Bot {
public:
	enum class State {
		Idle,
		Recording,
		Playing
	};

private:
	GT::PlayLayer* m_playlayer;
	unipair<Recorder> m_recorders;
	unipair<Player>   m_players;
	BotConfiguration  m_botConfig;
	
	State m_state = State::Idle;
	
	Bot() : m_players(true, false) {}
	
public:
	unipair<Recorder>& recorder();
	unipair<Player>& player();
	void bindObject(GT::PlayLayer* playLayer);
	
	void setState(State state) { m_state = state; }
	State getState() const { return m_state; }
	BotConfiguration& config() { return m_botConfig; }

	//Too many responsabilities on this class?
	SERDERR serialize(std::string const& name);
	SERDERR deserialize(std::string const& name);

	static Bot& get();

	Bot(const Bot&) = delete;
};