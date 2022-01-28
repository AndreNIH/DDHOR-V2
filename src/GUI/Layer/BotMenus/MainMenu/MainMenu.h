#pragma once
#include "../LevelLoader.h"
#include "../PopupLayer.h"
#include <cocos2d.h>

using namespace cocos2d;

class MainMenu : public PopupLayer{
private:
    bool setup() override;
public:
    MainMenu();
    CREATE_FUNC(MainMenu);
};