#include "RecordMenuLayer.h"
#include "MenuConstants.h"
#include "../TextboxUtils.h"
#include "Engine/Manager.h"
#include <filesystem>
#include <sstream>
using namespace cocos2d;

//==============================


void RecordMenuLayer::startRecording(){
    std::string str = m_macroNameInput->getString();
    short fps = std::stoi(m_fpsInput->getString());
    Bot::get().config().setMacroName(str + ".ddhor");
    Bot::get().config().setFPS(fps);
    Bot::get().setState(Bot::State::Recording);
    
    
    auto ctx = *LoaderProtocol::getLoaderContext();
    auto parent = reinterpret_cast<CCLayer*>(getParent());
    parent->setKeyboardEnabled(false);
    parent->setKeypadEnabled(false);
    parent->setTouchEnabled(false);
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(parent);
    CCDirector::sharedDirector()->getKeyboardDispatcher()->removeDelegate(parent);
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(parent);
    ctx.invokeLoader();
    onClose(this);
}

void RecordMenuLayer::FLAlert_Clicked(gd::FLAlertLayer*, bool btn2)
{
    if (btn2) startRecording();
}

void RecordMenuLayer::onRecord(CCObject* sender) {
    using std::filesystem::exists;
    std::string str = m_macroNameInput->getString();
    if (str.empty()) return;
    if(exists("ddhor/" + str + ".ddhor")) {
        const float size = CCDirector::sharedDirector()->getWinSize().width * 0.5;
        auto alert = gd::FLAlertLayer::create(
            this, 
            "Overwrite Macro", 
            "No", "Yes",
            size,
            "A macro with this name already exists. Do you wish to <cr>overwrite</c> it?"
        );
        alert->show();
        return;
    }

    startRecording();
}
void RecordMenuLayer::setup()
{
    const float inputWidgetWidth = m_layerSize.width * 0.80;
    const float inputWidgetHeight = m_layerSize.height * 0.15;
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    //Add header text
    CCLabelBMFont* headerText = CCLabelBMFont::create("Record Mode", "goldFont.fnt", 100, CCTextAlignment::kCCTextAlignmentCenter);
    headerText->setWidth(m_layerSize.width);
    headerText->setPositionX(winSize.width / 2);
    headerText->setPositionY(winSize.height / 2 + (m_layerSize.height / 2) - 20);
    addChild(headerText);


    //Add input fields - Macro Name
    m_macroNameInput = gd::CCTextInputNode::create("Macro Name", this, "chatFont.fnt", inputWidgetWidth, inputWidgetHeight);
    m_macroNameInput->setPositionX(winSize.width / 2);
    m_macroNameInput->setPositionY(winSize.height / 2 + 20);
    m_macroNameInput->setAllowedChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-0123456789 ");
    
    m_macroNameLabel = TextUtil::createTextLabel("Macro Name:", m_macroNameInput);
    
    addChild(TextUtil::createTextTint(m_macroNameInput));
    addChild(m_macroNameLabel);
    addChild(m_macroNameInput);

    //Add input fields - FPS
    m_fpsInput = gd::CCTextInputNode::create("FPS Value", this, "chatFont.fnt", inputWidgetWidth, inputWidgetHeight);
    m_fpsInput->setPositionX(winSize.width / 2);
    m_fpsInput->setPositionY(winSize.height / 2 - 35);
    m_fpsInput->setAllowedChars("0123456789");
    m_fpsInput->setMaxLabelLength(6);
    
    int fps = std::ceil(1.0 / CCDirector::sharedDirector()->getAnimationInterval());
    m_fpsInput->setString(std::to_string(fps).c_str());

    addChild(TextUtil::createTextLabel("FPS Value:", m_fpsInput));
    addChild(TextUtil::createTextTint(m_fpsInput));
    addChild(m_fpsInput);

    //Add go button
    CCSprite* btnSprite = gd::ButtonSprite::create("Record", 0, false, "goldFont.fnt", "GJ_button_01.png", 0.0f, 1.0f);
    auto btn = gd::CCMenuItemSpriteExtra::create(btnSprite, this, menu_selector(RecordMenuLayer::onRecord));
    btn->setSizeMult(1.25);
    
  
    
    CCMenu* menu = CCMenu::createWithItem(btn);
    menu->setPositionX(winSize.width / 2);
    menu->setPositionY((winSize.height / 2 - m_layerSize.height / 2) + btnSprite->getContentSize().height/2 +10);
    menu->setTouchPriority(-501);
    menu->setZOrder(3);
    addChild(menu);
    
}


RecordMenuLayer* RecordMenuLayer::create(float width, float height, const char* bgName)
{
    auto* p = new RecordMenuLayer;
    if (p && p->init(width, height, bgName)) {
        p->autorelease();
        return p;
    }
    else {
        CC_SAFE_DELETE(p);
        return nullptr;
    }
}

