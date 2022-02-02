#include "MainMenu.h"
#include <gd.h>
#include <utility>
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>
#include "PlaybackMenu.h"
#include  "RecorderMenu.h"

void MainMenu::onLoad(CCObject* sender){
    auto scene = CCDirector::sharedDirector()->getRunningScene();
    auto menu = PlaybackMenu::create();
    if(!menu) return;
    scene->addChild(menu,scene->getHighestChildZ()+1);
}

void MainMenu::onRecord(CCObject* sender){
    auto scene = CCDirector::sharedDirector()->getRunningScene();
    auto menu = RecorderMenu::create();
    if(!menu) return;
    scene->addChild(menu,scene->getHighestChildZ()+1);
}

void MainMenu::onNormal(CCObject* sender){

}



bool MainMenu::setup(){
    try{
        CCMenu* btnMenu = CCMenu::create();
        std::vector<std::pair<CCSprite*,SEL_MenuHandler>> mainButtons;
        mainButtons.emplace_back(CCSprite::createWithSpriteFrameName("D2B_RecordBtn_001.png"), menu_selector(MainMenu::onRecord));
        mainButtons.emplace_back(CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"), menu_selector(MainMenu::onNormal));
        mainButtons.emplace_back(CCSprite::createWithSpriteFrameName("D2B_LoadBtn_001.png"), menu_selector(MainMenu::onLoad));
        for(auto& btnItem : mainButtons){
            rtc::notNull(btnItem.first);
            gd::CCMenuItemSpriteExtra* menuItem = gd::CCMenuItemSpriteExtra::create(btnItem.first, this, btnItem.second);
            menuItem->setSizeMult(1.25);
            btnMenu->addChild(menuItem);
        }

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        btnMenu->alignItemsHorizontallyWithPadding(5);
        btnMenu->setPositionX(winSize.width / 2);
        btnMenu->setPositionY(winSize.height / 2);
        m_pLayer->addChild(btnMenu,1);

        CCLabelBMFont* headerText = CCLabelBMFont::create("Select Mode", "bigFont.fnt", 100, CCTextAlignment::kCCTextAlignmentCenter);
        headerText->setWidth(1000);
        headerText->setPositionY( winSize.height/2 + (_layerDimensions.height/2) - 22);
        headerText->setPositionX(winSize.width/2);
        m_pLayer->addChild(headerText,1);

        //Add zoom animation
        auto zoom = CCEaseOut::create(CCScaleTo::create(0.15,1.0), 0.5);
        m_pLayer->setScale(0);
        m_pLayer->runAction(zoom);

        //Add dark background
        auto tint = extension::CCScale9Sprite::create("square02_small.png", { 0,0, 40, 40 });
        tint->setContentSize(_layerDimensions);
        tint->setPosition({winSize.width/2, winSize.height/2});
        tint->setOpacity(60);
        tint->setScale(0.95f, 0.9f);
        m_pLayer->addChild(tint);

    }catch(const DEX::NullException& ex){
        LOG_EXCEPTION(ex, ex.what());
        return false;
    }
    
    return true;
}

MainMenu::MainMenu() : PopupLayer({350, 200}, "GJ_square01.png"){}