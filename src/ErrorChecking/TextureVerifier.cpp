#include "TextureVerifier.h"
#include <cocos2d.h>
#include <ErrorHandling/Logger.h>

bool TextureVerifier::runTest(){
    auto spriteCache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
    if(!spriteCache->spriteFrameByName(_textureName.c_str())){
        Logger::log()->warn(
            "[TextureVerifier] Failed test '{}': Could not find sprite '{}' loaded in memory", 
            ITest::getTestName(),
            _textureName
        );
        return false;
    }
    return true;
}

bool MultiTextureVerifier::runTest(){
    auto spriteCache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
    bool success=true;
    try{
        for(int i=_minNumber; i <= _maxNumber; i++){
            std::string targetTexture = fmt::format(_baseTexture, i);
            if(!spriteCache->spriteFrameByName(targetTexture.c_str())){
                Logger::log()->warn(
                    "[TextureVerifier] Failed test '{}': Could not find sprite '{}' loaded in memory", 
                    ITest::getTestName(),
                    targetTexture
                );
                success=false;
            }
        }
    }catch(const fmt::format_error& ex){
        LOG_EXCEPTION(ex, ex.what());
        return false;
    }
    return true;
}