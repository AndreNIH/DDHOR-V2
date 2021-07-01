#include "BMenuLayer.h"
#include "LoadMenuLayer.h"
#include "RecordMenuLayer.h"
#include "../Widget/ScalableMenuItemSprite.h"

#include <memory>
#include <stdexcept>

using namespace cocos2d;

namespace GUI {
    
    void BMenuLayer::onRecordLoad(CCObject* sender) {
        printf("BMenuLayer::onRecordLoad\n");
        auto layer = RecordMenuLayer::create(m_layerSize.width, m_layerSize.height, "GJ_square04.png");
        layer->setLoaderContext(LoaderProtocol::getLoaderContext());
        addChild(layer,3);

    }

    void BMenuLayer::onReplayLoad(CCObject* sender) {
        printf("BMenuLayer::onReplayLoad\n");
        auto layer = LoadMenuLayer::create(m_layerSize.width, m_layerSize.height, "GJ_square03.png");
        layer->setLoaderContext(LoaderProtocol::getLoaderContext());
        addChild(layer,3);
    }

    void BMenuLayer::onNormalLoad(CCObject* sender) {
        printf("BMenuLayer::onNormalLoad\n");
        LoaderProtocol::getLoaderContext()->invokeLoader();
    }
    
    void BMenuLayer::onOptions(CCObject* extra){
        typedef gd::FLAlertLayer*(*create_t)();
        typedef void(__thiscall *nextpage_t)(void*, int page);
        uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
        create_t   createOptionsMenu = reinterpret_cast<create_t>(base+0x1DE850);
        nextpage_t nextPage = reinterpret_cast<nextpage_t>(base+0x1E01B0);
        
        gd::FLAlertLayer* optionsMenu = createOptionsMenu();
        nextPage(optionsMenu,4);
        optionsMenu->show();
    }
    
    void BMenuLayer::setup() {
        CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(2);
        //Create Buttons Menu
        CCMenu* btnMenu = CCMenu::create();
        auto spNormalPlay =  std::make_pair(CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"),  (SEL_MenuHandler)&BMenuLayer::onNormalLoad);
        auto spBotRecord  =  std::make_pair(CCSprite::createWithSpriteFrameName("D2B_RecordBtn_001.png"),  (SEL_MenuHandler)&BMenuLayer::onRecordLoad);
        auto spBotPlayback = std::make_pair(CCSprite::createWithSpriteFrameName("D2B_LoadBtn_001.png"),  (SEL_MenuHandler)&BMenuLayer::onReplayLoad);
        if (!(spNormalPlay.first && spBotRecord.first && spBotPlayback.first)) throw std::runtime_error{"Not all sprites were created"};
        for (const auto& item : { spBotRecord,spNormalPlay,spBotPlayback }) {
            //auto isx = GUI::Widget::LoadingButton::create(this,item.second);
            auto isx = gd::CCMenuItemSpriteExtra::create(item.first, this, item.second);
            isx->setSizeMult(1.25);
            btnMenu->addChild(isx);
        }

        //Configure Menu
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        btnMenu->alignItemsHorizontallyWithPadding(5);
        btnMenu->setPositionX(winSize.width / 2);
        btnMenu->setPositionY(winSize.height / 2);
        m_pLayer->addChild(btnMenu,1);

        //Add text header
        CCLabelBMFont* headerText = CCLabelBMFont::create("Select Mode", "bigFont.fnt", 100, CCTextAlignment::kCCTextAlignmentCenter);
        headerText->setWidth(1000);
        headerText->setPositionY( winSize.height/2 + (m_layerSize.height/2) - 22);
        headerText->setPositionX(winSize.width/2);
        m_pLayer->addChild(headerText,1);
        
        //Add zoom animation
        auto zoom = CCEaseOut::create(CCScaleTo::create(0.15,1.0), 0.5);
        m_pLayer->setScale(0);
        m_pLayer->runAction(zoom);

        //Add dark background
        auto tint = extension::CCScale9Sprite::create("square02_small.png", { 0,0, 40, 40 });
        tint->setContentSize(m_layerSize);
        tint->setPosition({winSize.width/2, winSize.height/2});
        tint->setOpacity(60);
        tint->setScale(0.95f, 0.9f);
        m_pLayer->addChild(tint);

        //And change the Z order of the close button
        this->m_pButtonMenu->setZOrder(1);
        
        //Add settings button
        auto settingsSpr = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        auto settingsBtn = ScalableMenuItemSprite::create(settingsSpr, settingsSpr, this, menu_selector(BMenuLayer::onOptions));
        m_pButtonMenu->addChild(settingsBtn);
        
        settingsBtn->setScale(0.75f);
        settingsBtn->setPosition({-m_layerSize.width / 2 + settingsBtn->getScaledContentSize().width  + 2, m_layerSize.height / 2});
        //settingsSpr->setPositionX(closeBtnPos.x + closeBtnSize.width/2 + settingsBtn->getContentSize().width/2);
        //settingsSpr->setPositionY(closeBtnPos.y);

    }
    BMenuLayer* BMenuLayer::create(float width, float height, const char* bgName)
	{
        BMenuLayer* p = new BMenuLayer;
        if (p && p->init(width, height, bgName)) {
            p->autorelease();
            return p;
        }
        else {
            CC_SAFE_DELETE(p);
            return nullptr;
        }
	}

}