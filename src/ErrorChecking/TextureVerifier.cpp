#include "TextureVerifier.h"
#include <cocos2d.h>
#include <ErrorHandling/Logger.h>

bool TextureVerifier::runTest(){
    auto spriteCache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
    if(!spriteCache->spriteFrameByName(_textureName.c_str())){
        Logger::get().log()->warn(
            "[TextureVerifier] Failed test '{}': Could not find sprite '{}' loaded in memory", 
            ITest::getTestName(),
            _textureName
        );
        return false;
    }
    return true;
}