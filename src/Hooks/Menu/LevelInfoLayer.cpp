#include "LevelInfoLayer.h"
#include <matdash.hpp>
#include <GUI/Layer/BotMenus/MainMenu/MainMenu.h>
#include <GUI/Widget/ProgressButton.h>
#include <spdlog/spdlog.h>
using namespace cocos2d;



namespace Hook{
    bool LevelInfoLayer::_init(gd::LevelInfoLayer* self, gd::GJGameLevel* gamelevel){
        orig<&_init,Thiscall>(self, gamelevel);
        auto button = ProgressButton::create();
        auto pos = reinterpret_cast<CCNode*>(self->m_pPlayBtnMenu->getChildren()->objectAtIndex(0))->getPosition();
        button->setPosition(pos);
        button->setSizeMultiplier(1.25);
        self->m_pPlayBtnMenu->removeAllChildren();
        self->m_pPlayBtnMenu->addChild(button);
        return true;
    }

    bool LevelInfoLayer::memInit(){
        add_hook<&_init, Thiscall>(gd::base + 0x175DF0);
        return true;
    }
}