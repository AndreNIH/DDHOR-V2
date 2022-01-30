#pragma once
#include <cocos2d.h>
#include "../PopupLayer.h"
#include "../../LevelLoader.h"

using namespace cocos2d;

class MainMenu : public PopupLayer{
private:
    void onLoad(CCObject* sender);
    void onRecord(CCObject* sender);
    void onNormal(CCObject* sender);
    bool setup() override;
public:
    MainMenu();
    CREATE_FUNC(MainMenu);
};