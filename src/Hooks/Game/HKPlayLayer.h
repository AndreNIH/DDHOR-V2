#pragma once
#include <gd.h>

namespace Hook{
    namespace PlayLayer{
        bool _init(gd::PlayLayer* _this, gd::GJGameLevel* gameLevel); //Fix parameters for this later
        void _update(gd::PlayLayer* _this, float dt);
        void _resetLevel(gd::PlayLayer* _this);
        void _levelComplete(gd::PlayLayer* _this);
        void _onQuit(gd::PlayLayer* _this);
        void _pushButton(gd::PlayLayer* _this, int a1, bool left);
        void _releaseButton(gd::PlayLayer* _this, int a1, bool left);
        bool memInit();
    };
}