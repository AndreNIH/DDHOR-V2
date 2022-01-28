#include "ProgressButton.h"
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>
#include <vector>
#include <algorithm>
#include <fmt/format.h>
#include "../Layer/BotMenus/MainMenu/MainMenu.h"

CCSprite* ProgressButton::getDefaultSprite(){
    return CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
}

//===============================
// SELECTED, UNSELECTED, ACTIVATE
//===============================
void ProgressButton::selected(){
    restartButtonSprite();
    auto resize = cocos2d::CCScaleTo::create(0.3, _sizeMult);
    auto bounce = cocos2d::CCEaseBounceOut::create(resize);
    auto bounceActions = CCArray::create();
    bounceActions->addObject(bounce);
    bounceActions->addObject(CCDelayTime::create(0.5));
    bounceActions->addObject(CCCallFunc::create(this, callfunc_selector(ProgressButton::onBeginLoadingAnimation)));
    runAction(CCSequence::create(bounceActions));;
    CCMenuItemSprite::selected();
}

void ProgressButton::unselected(){
    CCMenuItemSprite::unselected();
    restartButtonSprite();
    auto resize = CCScaleTo::create(0.3, 1.0);
	auto bounce = CCEaseBounceOut::create(resize);
    runAction(bounce);
    setNormalImage(getDefaultSprite());
}

void ProgressButton::activate(){
    restartButtonSprite();
    runAction(CCScaleTo::create(0.0f, 1.0));
    setNormalImage(getDefaultSprite());
    auto scene = CCDirector::sharedDirector()->getRunningScene();
    if(scene->getChildByTag(MENULAYER_TAG) == nullptr) CCMenuItemSprite::activate();
}

//===============================
// Event Callbacks
//===============================

void ProgressButton::onLoadLevel(CCObject* sender){
    try{
        //todo
    }catch(const DEX::NullException& ex){
        LOG_EXCEPTION(ex);
    }
}

void ProgressButton::onBeginLoadingAnimation(){
    CCAnimation* loadingFrames  =  CCAnimation::createWithSpriteFrames(_loadingButtonSpriteFrames, 1.0 / 60.0);
    CCAnimate* loadingAnimation =  CCAnimate::create(loadingFrames);
    CCCallFunc* delegateInvocation=CCCallFunc::create(this, callfunc_selector(ProgressButton::onEndLoadingAnimation));
    auto actions = CCArray::create();
    actions->addObject(loadingAnimation);
    actions->addObject(delegateInvocation);
    auto sequence = CCSequence::create(actions);
    m_pNormalImage->runAction(sequence);
    m_pNormalImage->setPosition({ m_pNormalImage->getPositionX() - 2,m_pNormalImage->getPositionY() - 4 });
}

void ProgressButton::onEndLoadingAnimation(){
    setEnabled(false);
    auto scene = CCDirector::sharedDirector()->getRunningScene();
    auto menu  = MainMenu::create();
    menu->setTag(MENULAYER_TAG);
    scene->addChild(menu,2);
    unselected();
    setEnabled(true);
}

void ProgressButton::restartButtonSprite(){
    m_pNormalImage->stopAllActions();
    m_pNormalImage->setPosition({ 0,0 });
    setNormalImage(getDefaultSprite());
    stopAllActions();
}

void ProgressButton::setSizeMultiplier(float multiplier){
    _sizeMult=multiplier;
}

bool ProgressButton::init(){
    
    try{
        auto normalButtonSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
        _loadingButtonSpriteFrames = CCArray::createWithCapacity(31);
        rtc::notNull(normalButtonSprite);
        
        normalButtonSprite->retain();
        _loadingButtonSpriteFrames->retain();

        if(!CCMenuItemSprite::initWithNormalSprite(
            normalButtonSprite, 
            normalButtonSprite, 
            normalButtonSprite, 
            this, 
            menu_selector(ProgressButton::onLoadLevel))
        ) return false;
        

        CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        for(int i=0; i < _loadingButtonSpriteFrames->capacity();i++){
            std::string spriteName = fmt::format("GJ_loadPlayBtn_{:03}.png", i);
            CCSpriteFrame* frame = cache->spriteFrameByName(spriteName.c_str());
            rtc::notNull(frame);
            _loadingButtonSpriteFrames->addObject(frame);
        }        
        return true;
    }catch(const DEX::NullException& ex){
        LOG_EXCEPTION(ex, ex.what());
        return false;
    }
}

ProgressButton::~ProgressButton(){
    _loadingButtonSpriteFrames->release();
}