#pragma once
#include <gd.h>

namespace Hook{
    namespace LevelInfoLayer{
        bool _init(gd::LevelInfoLayer* self, gd::GJGameLevel* gamelevel);
        bool memInit();
    }

}