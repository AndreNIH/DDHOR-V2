#include <iostream>
#include <gd.h>
#include <matdash/boilerplate.hpp>
#include "Hooks/Game/HKPlayLayer.h"
#include "Hooks/Menu/LevelInfoLayer.h"
#include "Bot/Engine.h"

void mod_main(HMODULE mod){
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    gd::init();
    Hook::PlayLayer::memInit();
    Hook::LevelInfoLayer::memInit();

    
}