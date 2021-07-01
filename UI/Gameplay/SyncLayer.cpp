#include "SyncLayer.h"
#include "Engine/Manager.h"
#include "Hooks/HookManger.h"
#include "../GDTypes/CheckpointObject.h"
#include <Speedhack.h>
#include <GameController.h>
const int SyncLayer::SEQ_TAG = 5599;
const int SyncLayer::TAG = 5598;

using namespace cocos2d;
std::string SyncLayer::actEnumToString(Act act){
	return act == Act::PUSH
		? "PUSH"
		: "RELEASE";
}

cocos2d::CCLabelBMFont* SyncLayer::generateMenuLabel(int playerN, Act act){
	std::string str = "Player " + std::to_string(playerN) + ": " + actEnumToString(act) + " to respawn";
	return CCLabelBMFont::create(str.c_str(), "bigFont.fnt");;
}


void SyncLayer::endRespawn() {
	typedef void(__thiscall* ret)(void*);
	auto respawn = HookManager::get().getFunctionPtr<ret>("44d64426e029288cee9f53ca9e668e55ad40f26ee88334f5c284ba79ba5311c9");
	respawn(m_playLayer);
	hide();
}

void SyncLayer::cancelRespawn(){
	if (auto action = getActionByTag(SEQ_TAG)) {
		stopAction(action);
		setOpacity(255);
	}
}

void SyncLayer::beginRespawn(){
	if (getActionByTag(SEQ_TAG) == nullptr) {
		auto seqItems = CCArray::create();
		seqItems->addObject(CCFadeTo::create(0.3, 0));
		seqItems->addObject(CCCallFunc::create(this, callfunc_selector(SyncLayer::endRespawn)));
		auto seq = CCSequence::create(seqItems);
		seq->setTag(SEQ_TAG);
		runAction(seq);
	}
}

void SyncLayer::setOpacity(GLubyte opacity)
{
	CCLayerColor::setOpacity(opacity);
	CCObject* child;
	CCARRAY_FOREACH(m_pChildren, child){
		CCNode* pNode = (CCNode*)child;
		cocos2d::CCRGBAProtocol* pRGBAProtocol = dynamic_cast<cocos2d::CCRGBAProtocol*>(pNode);
		if (pRGBAProtocol) pRGBAProtocol->setOpacity(opacity);
	};
}

void SyncLayer::show(){
	/*m_animationSpeed = cocos2d::CCDirector::sharedDirector()->getScheduler()->getTimeScale();
	cocos2d::CCDirector::sharedDirector()->getScheduler()->setTimeScale(1);*/
	GameController::suspend();
	m_bypassWait = true;
	scheduleUpdate();
	setOpacity(255);
	setVisible(true);

}

void SyncLayer::hide(){
	//cocos2d::CCDirector::sharedDirector()->getScheduler()->setTimeScale(m_animationSpeed);
	GameController::commit();
	unscheduleUpdate();
	setOpacity(0);
	setVisible(false);
}

void SyncLayer::syncPlayerActions(const std::optional<Act>& p1, const std::optional<Act>& p2){
	typedef void(__thiscall* btnFunction)(void*, int, bool);
	typedef void(__fastcall* btnHFunction)(void*, int,int, bool);
	uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
	btnHFunction releaseHook = reinterpret_cast<btnHFunction>(base + 0x111660);
	btnFunction releaseOriginal = HookManager::get().getFunctionPtr<btnFunction>("cb5a1230ab8154e622c7ba3314c2918add7f6285e5a7324d700553d30af151f1");
	if(p1.has_value() && (p1.value() == Act::RELEASE && (m_reportedActionP1 == Act::PUSH))) 
		releaseHook(m_playLayer, 0, 0, true);
	else if(!p1.has_value()) 
		releaseOriginal(m_playLayer,0,true);
	if(p2.has_value() && (p2.value() == Act::RELEASE && (m_reportedActionP2 == Act::PUSH))) 
		releaseHook(m_playLayer,0 , 0, false);
	else if(!p2.has_value()) 
		releaseOriginal(m_playLayer,0,false);
}

void SyncLayer::update(float dt){
	if (m_playLayer == nullptr) return;
	GT::CheckpointObject* checkpoint = reinterpret_cast<GT::CheckpointObject*>(m_playLayer->checkpointArray->lastObject());
	auto& [p1, p2] = Bot::get().recorder();
	
	const float newPos = checkpoint ? checkpoint->playerCheckpoint->xPos : 0.0f;
	p1.rollback(newPos);
	p2.rollback(newPos);
	if(Bot::get().config().getNoSyncLayer()) {
		endRespawn();
		syncPlayerActions(p1.lastAction(),p2.lastAction());
		return;
	}
	const bool respawn1 =  (!p1.lastAction().has_value() && m_reportedActionP1 == Act::RELEASE) || p1.lastAction() == m_reportedActionP1;
	const bool respawn2 =  (!p2.lastAction().has_value() && m_reportedActionP2 == Act::RELEASE) || p2.lastAction() == m_reportedActionP2;
	if (!(m_cacheRespawnP1 == respawn1 && m_cacheRespawnP2 == respawn2)) {
		m_cacheRespawnP1 = respawn1;
		m_cacheRespawnP2 = respawn2;
		m_labelsMenu->removeAllChildren();
		m_labelsMenu->addChild(CCLabelBMFont::create("You Died", "goldFont.fnt"));
		//False statement in ternary condition handles respawning when there are no recorded actions, respawn without pressing mouse button
		if (!respawn1) m_labelsMenu->addChild(generateMenuLabel(1, p1.lastAction().has_value() ? p1.lastAction().value() : Act::RELEASE));
		if (!respawn2) m_labelsMenu->addChild(generateMenuLabel(2, p2.lastAction().has_value() ? p2.lastAction().value() : Act::RELEASE));
		m_labelsMenu->alignItemsVerticallyWithPadding(10);
	}

	//Last minute fix for manually restarting levels, when no chekpoints are available
	//if(checkpoint == nullptr && (m_reportedActionP1 == Act::RELEASE))
	//if (respawn1 && respawn2 && m_bypassWait) endRespawn();
	bool noFade   = Bot::get().config().getNoSyncFadeout();
	
	if (respawn1 && respawn2 && (noFade || m_bypassWait)) endRespawn();
	else if (respawn1 && respawn2) beginRespawn();
	else cancelRespawn();
	m_bypassWait = false;
}

bool SyncLayer::init(){
	if (!CCLayerColor::initWithColor({0,0,0,0})) return false;
	m_labelsMenu = CCMenu::create();
	
	addChild(m_labelsMenu);
	return true;
}
