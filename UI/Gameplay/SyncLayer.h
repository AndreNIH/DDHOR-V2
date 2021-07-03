#pragma once
#include <gd.h>
#include <Engine/BotActions.h>
#include <optional>
#include "../GDTypes/PlayLayer.h"

class SyncLayer : public cocos2d::CCLayerColor{
private:
	static const int SEQ_TAG;
	GT::PlayLayer* m_playLayer;
	cocos2d::CCSequence* m_seqRespawn = nullptr;
	cocos2d::CCMenu* m_labelsMenu = nullptr;
	Act m_reportedActionP1 = Act::RELEASE;
	Act m_reportedActionP2 = Act::RELEASE;
	bool m_bypassWait = true;
	bool m_cacheRespawnP1 = true;
	bool m_cacheRespawnP2 = true;

	float m_animationSpeed = 1; //Legacy
	float m_speedhackValue = 1;
	bool m_schedulerFrozen = false;
	
	std::string actEnumToString(Act act);
	cocos2d::CCLabelBMFont* generateMenuLabel(int playerN, Act act);

	void endRespawn();
	void cancelRespawn();
	void beginRespawn();

	void syncPlayerActions(const std::optional<Act>& p1, const std::optional<Act>& p2);
public:
	
	static const int TAG;
	void bindPlayLayer(GT::PlayLayer* playLayer) { m_playLayer = playLayer; }
	bool shouldEnterDual();
	void reportForP1(Act action) { m_reportedActionP1 = action; }
	void reportForP2(Act action) { m_reportedActionP2 = action; }

	void show();
	void hide();
	
	
	void setOpacity(GLubyte opacity);
	void update(float dt) override;
	bool init() override;
	CREATE_FUNC(SyncLayer);
};

