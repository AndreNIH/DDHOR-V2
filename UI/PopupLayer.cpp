#include "PopupLayer.h"
#include <cassert>
using namespace cocos2d;

void PopupLayer::registerWithTouchDispatcher() {
	auto td = cocos2d::CCDirector::sharedDirector()->getTouchDispatcher();
	int prio = td->getTargetPrio() - 1;
	td->setTargetPrio(prio);
	td->addTargetedDelegate(this, prio, true);
}

bool PopupLayer::init(float width, float height, const char* bgName)
{
	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	m_layerSize = cocos2d::CCSize{ width, height };
	if (!initWithColor({ 0, 0, 0, 75 }))
		return false;
	
	this->setKeyboardEnabled(true);
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
	CCDirector::sharedDirector()->getKeyboardDispatcher()->addDelegate(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->setForcePrio(2);

	//CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, CCDirector::sharedDirector()->getTouchDispatcher()->getForcePrio()-1);
	m_pLayer = cocos2d::CCLayer::create();
	addChild(this->m_pLayer);

	auto bg = extension::CCScale9Sprite::create(bgName, { 0.0f, 0.0f, 80.0f, 80.0f });
	bg->setContentSize(m_layerSize);
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	m_pLayer->addChild(bg);

	this->m_pButtonMenu = cocos2d::CCMenu::create();
	this->m_pLayer->addChild(this->m_pButtonMenu);
	setup();

	auto closeSpr = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
	closeSpr->setScale(.8f);

	gd::CCMenuItemSpriteExtra* closeBtn = gd::CCMenuItemSpriteExtra::create(closeSpr, this, (cocos2d::SEL_MenuHandler)&PopupLayer::onClose);
	closeBtn->setUserData(reinterpret_cast<void*>(this));

	m_pButtonMenu->addChild(closeBtn);
	closeBtn->setPosition(-width / 2, height / 2);




	return true;
}

void PopupLayer::onClose(cocos2d::CCObject*){
	setKeyboardEnabled(false);
	setKeypadEnabled(false);
	setTouchEnabled(false);
	CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
	CCDirector::sharedDirector()->getKeyboardDispatcher()->removeDelegate(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	removeFromParentAndCleanup(true);
}

void PopupLayer::keyDown(cocos2d::enumKeyCodes key)
{
	//if (key == enumKeyCodes::KEY_Escape) onClose(this);
	if (key != enumKeyCodes::KEY_Space)  gd::FLAlertLayer::keyDown(key);

}

void PopupLayer::keyBackClicked()
{
	onClose(this);
}
