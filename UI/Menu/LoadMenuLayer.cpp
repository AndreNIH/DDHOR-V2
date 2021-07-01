#include "LoadMenuLayer.h"
#include "MenuConstants.h"
#include "../Widget/ListWidget.h"
#include "Engine/Manager.h"
#include <filesystem>

using namespace cocos2d;
namespace fs = std::filesystem;
//========================================
// Delegates
//========================================


void LoadMenuLayer::textChanged(gd::CCTextInputNode* sender){
    m_fileDropdown->setDisplayFilter(sender->getString());
    m_fileDropdown->setPositionY(m_macroNameInput->getPositionY() - m_fileDropdown->getContentSize().height / 2 - 12);
}

void LoadMenuLayer::dropdownItemSelected(ListItem* item)
{
    m_macroNameInput->setString(item->getText().c_str());
}

void LoadMenuLayer::scrollWheel(float x, float y)
{
    int index = m_fileDropdown->getDisplayIndex();
    if (x > 0) m_fileDropdown->setDisplayIndex(index + 1);
    else m_fileDropdown->setDisplayIndex(index -1);
    m_fileDropdown->setPositionY(m_macroNameInput->getPositionY() - m_fileDropdown->getContentSize().height / 2 - 12);
}

//=========================
//Touch Handler
//==========================

void LoadMenuLayer::ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
{
    PopupLayer::ccTouchEnded(pTouch, pEvent);
    CCRect boundingBox = {
        m_macroNameInput->getPositionX() - m_macroNameInput->getContentSize().width  * m_macroNameInput->getAnchorPoint().x,
        m_macroNameInput->getPositionY() - m_macroNameInput->getContentSize().height * m_macroNameInput->getAnchorPoint().y,
        m_macroNameInput->getContentSize().width,m_macroNameInput->getContentSize().height
    };
    
    if (boundingBox.containsPoint(pTouch->getLocation())) m_fileDropdown->setVisible(true);
    else m_fileDropdown->setVisible(false);
}

void LoadMenuLayer::onLoad(cocos2d::CCObject* sender)
{
    m_errorLabel->setVisible(false);
    m_fileDropdown->setVisible(false);
    std::string path = m_macroNameInput->getString();
    path += ".ddhor";

    auto err = Bot::get().deserialize(path);
    if (err == SERDERR::FileNotFound) {
        m_errorLabel->setVisible(true);
        m_errorLabel->setString("Macro does not exist");
        m_errorLabel->setPositionX((m_macroNameInput->getPositionX() / 2) + m_errorLabel->getScaledContentSize().width / 2);
        return;
    }

    if (err == SERDERR::DerErr) {
        m_errorLabel->setVisible(true);
        m_errorLabel->setString("The selected macro is invalid");
        m_errorLabel->setPositionX((m_macroNameInput->getPositionX() / 2) + m_errorLabel->getScaledContentSize().width / 2);
        return;
    }

    
    Bot::get().setState(Bot::State::Playing);
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

std::vector<std::string> LoadMenuLayer::getMacroFiles()
{
    std::vector<std::string>files;
    for (auto& f : fs::directory_iterator("ddhor")) {
        if (f.path().extension() != ".ddhor") continue;
        files.push_back(f.path().stem().string());
    }
    return files;
}

void LoadMenuLayer::onMacroBrowser(cocos2d::CCObject* sender){
    const float size = CCDirector::sharedDirector()->getWinSize().width * 0.7;
    auto alert = gd::FLAlertLayer::create(this, "Feature Unavaliable", "Ok", nullptr, size,
        "This button corresponds to the bot's macro file explorer. This feature is yet to be implemented.\n\r"
        "It will be introduced in a <cr>future update</c>"
    );
    
    alert->show();
}

//========================================
void LoadMenuLayer::setup(){
    setMouseEnabled(true);
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //Add header text
    CCLabelBMFont* headerText = CCLabelBMFont::create("Playback Mode", "goldFont.fnt", 100, CCTextAlignment::kCCTextAlignmentCenter);
    headerText->setWidth(m_layerSize.width);
    headerText->setPositionX(winSize.width / 2);
    headerText->setPositionY(winSize.height / 2 + (m_layerSize.height / 2) - 20);
    m_pLayer->addChild(headerText);

    //Add input fields - Macro Name
    const double inputWidgetWidth = m_layerSize.width * 0.80;
    const double inputWidgetHeight = m_layerSize.height * 0.15;
    m_macroNameInput = gd::CCTextInputNode::create("Macro Name", this, "chatFont.fnt", inputWidgetWidth, inputWidgetHeight);
    m_macroNameInput->setPositionX(winSize.width / 2);
    m_macroNameInput->setPositionY(winSize.height / 2 + 20);
    m_macroNameInput->setDelegate(this);
    m_macroNameInput->setAllowedChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-0123456789 ");
    
    m_pLayer->addChild(TextUtil::createTextLabel("Macro Name:", m_macroNameInput));
    m_pLayer->addChild(TextUtil::createTextTint(m_macroNameInput));
    m_pLayer->addChild(m_macroNameInput);

    //Add error label;
    m_errorLabel = TextUtil::createTextLabel("", m_macroNameInput);//CCLabelBMFont::create();
    m_errorLabel->setVisible(false);
    m_errorLabel->setColor(ccRED);
    m_errorLabel->setPositionY(m_macroNameInput->getPositionY() - m_macroNameInput->getContentSize().height/2 - 10);
    m_pLayer->addChild(m_errorLabel);

    const int menuPriority = -700;

    //Add dropdown menu
    const double dropdownWidth = MenuDimension::WIDTH * 0.8;
    const double dropdownHeight = MenuDimension::HEIGHT * 0.1;
    m_fileDropdown = DropdownList::create({ dropdownWidth,dropdownHeight });
    m_fileDropdown->setListDelegate(this);
    m_fileDropdown->addListElements(getMacroFiles());
    m_fileDropdown->setMaxItemDisplay(3);
    m_fileDropdown->setPadding(2);
    m_fileDropdown->setPositionX(winSize.width / 2);
    m_fileDropdown->setPositionY(m_macroNameInput->getPositionY() - m_fileDropdown->getContentSize().height / 2 - 12);
    //m_fileDropdown->setTouchPriority(menuPriority);
    m_fileDropdown->setVisible(false);
    m_pLayer->addChild(m_fileDropdown);
    
    //Add file exporer button
    CCSprite* folderSprite = CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png");
    folderSprite->setScale(0.8);
    auto folderBtn = gd::CCMenuItemSpriteExtra::create(folderSprite,this, menu_selector(LoadMenuLayer::onMacroBrowser));
    folderBtn->setSizeMult(1.25);
    folderBtn->setUserData(this);
    CCMenu* folderMenu = CCMenu::createWithItem(folderBtn);
    folderMenu->setPosition({ winSize.width / 2, winSize.height / 2 });
    folderMenu->setPositionY(m_macroNameInput->getPositionY());
    folderMenu->setPositionX(m_macroNameInput->getPositionX()  + m_macroNameInput->getContentSize().width/2 + 15);
    //folderMenu->setTouchPriority(menuPriority);
    m_pLayer->addChild(folderMenu);
    
    //Add Load button
    CCSprite* btnSprite = gd::ButtonSprite::create("Load", 0, false, "goldFont.fnt", "GJ_button_01.png", 0.0f, 1.0f);
    auto btn = gd::CCMenuItemSpriteExtra::create(btnSprite, this, menu_selector(LoadMenuLayer::onLoad));
    btn->setSizeMult(1.25);
    
    CCMenu* menu = CCMenu::createWithItem(btn);
    menu->setPositionX(winSize.width / 2);
    menu->setPositionY((winSize.height / 2 - m_layerSize.height / 2) + btnSprite->getContentSize().height / 2 + 10);
    //menu->setTouchPriority(menuPriority);
    //menu->setZOrder(3);
    m_pLayer->addChild(menu);
    m_pLayer->setZOrder(0);

}


LoadMenuLayer* LoadMenuLayer::create(float width, float height, const char* bgName)
{
    auto* p = new LoadMenuLayer;
    if (p && p->init(width, height, bgName)) {
        p->autorelease();
        return p;
    }
    else {
        CC_SAFE_DELETE(p);
        return nullptr;
    }
}