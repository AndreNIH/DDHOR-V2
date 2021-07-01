#pragma once
#include <cocos2d.h>

class GreetingLayer : public cocos2d::CCLayer{
private:
    void removeCallback();
public:
    bool init() override;
    void setOpacity(GLubyte opacity);
    CREATE_FUNC(GreetingLayer);
};