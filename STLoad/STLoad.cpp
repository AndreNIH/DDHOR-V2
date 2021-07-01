#include "STLoad.h"
#include <Keyboard/KBHooks.h>
#include "../UI/Greeting/Greeting.h"
using namespace cocos2d;

STLoad& STLoad::get() {
    static STLoad instance;
    return instance;
}

void STLoad::loadResources()
{
    auto spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    spriteCache->addSpriteFramesWithFile("DS_PlayButton.plist");
    spriteCache->addSpriteFramesWithFile("DS_Menu.plist");
    //spriteCache->addSpriteFramesWithFile("LoadButton.plist");
}

void STLoad::hookKeyboard(){
    WHK::init(GetCurrentThreadId());
}

void STLoad::invokeLoader(float dt)
{
    auto scene = CCDirector::sharedDirector()->getRunningScene();
    auto scheduler = cocos2d::CCDirector::sharedDirector()->getScheduler();
    scheduler->unscheduleSelector(schedule_selector(STLoad::invokeLoader), this);
    scene->addChild(GreetingLayer::create(),scene->getHighestChildZ()+1);
    loadResources();
    hookKeyboard();
}

STLoad::~STLoad(){
    auto spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    spriteCache->removeSpriteFrameByName("DS_PlayButton.plist");
    spriteCache->removeSpriteFrameByName("DS_Menu.plist");
    WHK::release();
}