#include "PopupLayer.h"
#include <cocos-ext.h>
#include <cassert>
using namespace cocos2d;

PopupLayer::PopupLayer(const CCSize& dimension, const std::string& background) : 
    _layerDimensions(dimension), 
    _backgroundImage(background){}


void PopupLayer::enableLayerInput(){
	auto director = CCDirector::sharedDirector();
    this->setKeyboardEnabled(true);
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	director->getTouchDispatcher()->setForcePrio(2);
}

void PopupLayer::onClose(CCObject* sender){
	setKeyboardEnabled(false);
	setKeypadEnabled(false);
	setTouchEnabled(false);
	CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
	CCDirector::sharedDirector()->getKeyboardDispatcher()->removeDelegate(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	removeFromParent();
}

void PopupLayer::keyDown(enumKeyCodes key){
	if (key != enumKeyCodes::KEY_Space)  gd::FLAlertLayer::keyDown(key);
}

void PopupLayer::keyBackClicked(){
	onClose(this);
}

void PopupLayer::registerWithTouchDispatcher(){
	auto touchDispatcher = cocos2d::CCDirector::sharedDirector()->getTouchDispatcher();
	int prio = touchDispatcher->getTargetPrio() - 1;
	touchDispatcher->setTargetPrio(prio);
	touchDispatcher->addTargetedDelegate(this, prio, true);
}

bool PopupLayer::init(){
    auto director = CCDirector::sharedDirector();
    CCSize winSize = director->getWinSize();
	if (!CCLayerColor::initWithColor({ 0, 0, 0, 75 })) return false;
    enableLayerInput(); //Activate controls and add delegates

    
    m_pLayer = cocos2d::CCLayer::create(); //Create Layer Body
	addChild(this->m_pLayer);

    auto bg = extension::CCScale9Sprite::create(_backgroundImage.c_str(), { 0.0f, 0.0f, 80.0f, 80.0f }); //Create a background for the new layer
	bg->setContentSize(_layerDimensions);
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	m_pLayer->addChild(bg); //Bind background to Body Layer

    gd::FLAlertLayer::m_pButtonMenu = cocos2d::CCMenu::create(); //Create Menu for the layer's Close Button
    gd::FLAlertLayer::m_pLayer->addChild(this->m_pButtonMenu);   //Bind Menu to Layer's Body
    CCSprite* closeSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"); //Create Close Button Sprite
    gd::CCMenuItemSpriteExtra* closeBtn = gd::CCMenuItemSpriteExtra::create(closeSpr, this, menu_selector(PopupLayer::onClose)); //Create Close Button
	closeSpr->setScale(.8f);
    closeBtn->setUserData(reinterpret_cast<void*>(this));
    m_pButtonMenu->addChild(closeBtn);
    closeBtn->setPosition(-_layerDimensions.width / 2, _layerDimensions.height / 2);
    return this->setup();
}


PopupLayer::~PopupLayer(){

}