#include "TextureLoader.h"
#include <ErrorHandling/Logger.h>
void TextureLoader::loadTexturesImpl(float dt){
    auto spriteCache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
    spriteCache->addSpriteFramesWithFile("DS_PlayButton.plist");
    spriteCache->addSpriteFramesWithFile("DS_Menu.plist");
    this->release();
    try{
        _cbLoadReady();
    }
    catch(const std::bad_function_call& ex){
        LOG_EXCEPTION(ex, "texturesLoaded callback was empty")
        MessageBoxA(
            NULL,
            "An unexpected error has occurred. Texture loading could not be verified. Please re-start your game",
            "Texture Loader Error",
            MB_ICONERROR
        );
    }
}

void TextureLoader::loadTextures(const Callback& callback){
    using namespace cocos2d;
    TextureLoader* instance = new TextureLoader(callback);
    instance->autorelease();
    instance->retain();
    CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
    scheduler->scheduleSelector(
        schedule_selector(TextureLoader::loadTexturesImpl),  //Selector
        instance,                                            //Instance
        0.0f,                                                //Interval
        0,                                                   //Repeat                   
        0,                                                   //Delay
        false                                                //Paused
    );
    
}