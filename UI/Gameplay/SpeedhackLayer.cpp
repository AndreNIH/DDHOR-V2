#include "SpeedhackLayer.h"
#include <Engine/Manager.h>
#include "../TextboxUtils.h"
#include <Speedhack.h>
#include <GameController.h>
using namespace cocos2d;

void SpeedhackLayer::onClose(CCObject* sender) {
    auto pauseLayer = m_pauseLayer;
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
    auto onResume = reinterpret_cast<void(__thiscall*)(void*, void*)>(base + 0x1E5FA0);
    onResume(reinterpret_cast<CCLayer*>(getParent()) , nullptr);
    
    CCDirector::sharedDirector()->getOpenGLView()->showCursor(false);
    PopupLayer::onClose(sender);
    GameController::commit();
}
void SpeedhackLayer::onUpdateSpeed(cocos2d::CCObject* sender){
    
    std::string str = m_newSpeed->getString();
    if (str.empty()) return;
    float val = std::stof(str);
    if (val == 0) return;
    //Bot::get().config().setSpeed(val);
    GameController::setSpeed(val);
    onClose(this);
}

void SpeedhackLayer::setup(){
    CCDirector::sharedDirector()->getOpenGLView()->showCursor(true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    const float inputWidgetWidth = m_layerSize.width * 0.25;
    const float inputWidgetHeight = m_layerSize.height * 0.20;
    //Reset speed and schedulers
    GameController::suspend();

    //CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);

    //Create header
    CCLabelBMFont* headerText = CCLabelBMFont::create("Speedhack Menu", "goldFont.fnt", 100, CCTextAlignment::kCCTextAlignmentCenter);
    headerText->setWidth(m_layerSize.width);
    headerText->setPositionX(winSize.width / 2);
    headerText->setPositionY(winSize.height / 2 + (m_layerSize.height / 2) - 20);
    addChild(headerText);

    //Create input
    float speed = GameController::getSpeed();
    std::stringstream iss;
    iss << std::fixed << std::setprecision(3) << speed;

    m_newSpeed = gd::CCTextInputNode::create("Speed", this, "chatFont.fnt", inputWidgetWidth, inputWidgetHeight);
    m_newSpeed->setString(iss.str().c_str());
    m_newSpeed->setPositionX(winSize.width / 2);
    m_newSpeed->setPositionY(winSize.height / 2);
    m_newSpeed->setAllowedChars("0123456789.");

    auto tint = extension::CCScale9Sprite::create("square02_small.png", { 0,0, 40, 40 });
    tint->setContentSize({ m_newSpeed->getContentSize().width*2,m_newSpeed->getContentSize().height*2 });
    tint->setScale(0.5);
    tint->setPosition(m_newSpeed->getPosition());
    tint->setOpacity(100);
    m_pLayer->addChild(tint);
    m_pLayer->addChild(m_newSpeed);

    //Create Set Button
    CCSprite* btnSprite = gd::ButtonSprite::create("Set", 0, false, "goldFont.fnt", "GJ_button_01.png", 0.0f, 1.0f);
    auto btn = gd::CCMenuItemSpriteExtra::create(btnSprite, this, menu_selector(SpeedhackLayer::onUpdateSpeed));
    btn->setSizeMult(1.25);
    CCMenu* menu = CCMenu::createWithItem(btn);
    menu->setPositionX(winSize.width / 2);
    menu->setPositionY((winSize.height / 2 - m_layerSize.height / 2) + btnSprite->getScaledContentSize().height / 2 + 10);
    m_pLayer->addChild(menu);

    //Hide close button
    //removeCloseBtn();
}

SpeedhackLayer* SpeedhackLayer::create(float width, float height, const char* bgName){
    SpeedhackLayer* p = new SpeedhackLayer;
    if (p && p->init(width, height, bgName)) {
        p->autorelease();
        return p;
    }
    else {
        CC_SAFE_DELETE(p);
        return nullptr;
    }
}

SpeedhackLayer::SpeedhackLayer(){}