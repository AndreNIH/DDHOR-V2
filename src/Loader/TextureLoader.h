#pragma once
#include <cocos2d.h>
#include <functional>
class TextureLoader : public cocos2d::CCObject
{
private: 
    using Callback = std::function<void()>;
    Callback _cbLoadReady=nullptr;
    void loadTexturesImpl(float dt);
    TextureLoader(const Callback& callback) : _cbLoadReady(callback){}
public:  
    static void loadTextures(const Callback& callback);
};
