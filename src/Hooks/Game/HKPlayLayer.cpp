#include "HKPlayLayer.h"
#include <matdash/minhook.hpp>
#include <matdash.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include "../../Bot/Engine.h"
using namespace cocos2d;
Bot bot;
namespace Hook{
    bool PlayLayer::_init(gd::PlayLayer* _this, gd::GJGameLevel* gameLevel){
        spdlog::info("PlayLayer::init");
        bot.importMacro("macro.ddhor");
        return orig<&PlayLayer::_init, Thiscall>(_this, gameLevel);
    }

    void PlayLayer::_update(gd::PlayLayer* _this, float dt){
        //spdlog::info("PlayLayer::update, dt={}", dt);
        bot.update();
        return orig<&PlayLayer::_update, Thiscall>(_this, 1.0f/ bot.getFPS());
    }

    void PlayLayer::_resetLevel(gd::PlayLayer* _this){
        spdlog::info("PlayLayer::resetLevel");
        orig<&PlayLayer::_resetLevel, Thiscall>(_this);
        bot.rewind();
    }

    void PlayLayer::_levelComplete(gd::PlayLayer* _this){
        spdlog::info("PlayLayer::levelComplete");
        return orig<&PlayLayer::_levelComplete, Thiscall>(_this);
    }

    void PlayLayer::_onQuit(gd::PlayLayer* _this){
        spdlog::info("PlayLayer::onQuit");
        return orig<&PlayLayer::_onQuit, Thiscall>(_this);
    }

    void PlayLayer::_pushButton(gd::PlayLayer* _this, int a1, bool left){
        spdlog::info("PlayLayer::pushButton");
        return orig<&PlayLayer::_pushButton, Thiscall>(_this, a1, left);
    }
    
    void PlayLayer::_releaseButton(gd::PlayLayer* _this, int a1, bool left){
        spdlog::info("PlayLayer::releaseButton");
        return orig<&PlayLayer::_releaseButton, Thiscall>(_this, a1, left);
    }

    bool PlayLayer::memInit(){
        add_hook<&PlayLayer::_init, Thiscall>(gd::base+0x1FB780);
        add_hook<&PlayLayer::_update, Thiscall>(gd::base+0x2029C0);
        add_hook<&PlayLayer::_resetLevel, Thiscall>(gd::base+0x20BF00);
        add_hook<&PlayLayer::_levelComplete, Thiscall>(gd::base+0x1FD3D0);
        add_hook<&PlayLayer::_onQuit, Thiscall>(gd::base+0x20D810);
        add_hook<&PlayLayer::_pushButton, Thiscall>(gd::base+0x111500);
        add_hook<&PlayLayer::_releaseButton, Thiscall>(gd::base+0x111660);
        return true;
    }

}