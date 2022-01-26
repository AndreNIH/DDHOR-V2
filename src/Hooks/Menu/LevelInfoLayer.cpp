#include "LevelInfoLayer.h"
#include <matdash.hpp>

namespace Hook{
    bool LevelInfoLayer::_init(gd::LevelInfoLayer* self, gd::GJGameLevel* gamelevel){
        orig<&_init,Thiscall>(self, gamelevel);
        //self->m_pPlayBtnMenu->removeFromParent();
        return true;
    }

    bool LevelInfoLayer::memInit(){
        add_hook<&_init, Thiscall>(gd::base + 0x175DF0);
        return true;
    }
}