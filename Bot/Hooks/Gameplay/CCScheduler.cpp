#include "CCScheduler.h"
#include <cocos2d.h>
#include <Hooks/HookManger.h>
#include <Engine/Manager.h>
#include <cmath>
#include <Windows.h>
#include <STIO.h>
#include <Engine/Manager.h>
#include "../../UI/Gameplay/FrameOverlayLayer.h"
#include <GameController.h>
bool skip = false;
void handleKeyboardEvents(){
    if(auto msg = STIO::get().fetchMsg()){
        if(Bot::get().config().getSuspendIO()) return;
        switch(msg.value().vKeyCode){
            case 'Q':
                //Toggle frame-skip
                if(msg.value().keyPressed){
                    bool val = !GameController::getPaused();
                    GameController::setPaused(val);
                    GameController::commit();
                }
                break;
            case 'W':
                //Advance frame skip
                if(!msg.value().keyPressed) break;
                skip = true;
        }
    }
}

void(__thiscall* o_update)(void*, float);
void __fastcall HK::CCScheduler::update(void* self, float dt){
    handleKeyboardEvents();
    if(GameController::getPaused()){
        auto scene = cocos2d::CCDirector::sharedDirector()->getRunningScene();
        if(scene->getChildByTag(FrameOverlayLayer::LAYER_IDENTIFIER) == nullptr)
            scene->addChild(FrameOverlayLayer::create(), 50);
        if(skip) skip = false;
        else return;
    }

    if(Bot::get().getState() != Bot::State::Idle){
        auto& config = Bot::get().config();
        float newDt = !config.getNoDeltaOverride() ? 1.0 / config.getFPS() : dt;
        //float newDt = true ? 1.0 / config.getFPS() : dt;
        o_update(self, newDt);
    }else{
        o_update(self, dt);
    }
}

void HK::CCScheduler::memInit(){
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandleA("libcocos2d.dll"));
    HookManager::get().addHook("12eb0c1692dcd71002f1bce01f88a2845ebdd731d1a481e3ea0b7086cad8095f",  base+0x103430,HK::CCScheduler::update);
    o_update = HookManager::get().getFunctionPtr<decltype(o_update)>("12eb0c1692dcd71002f1bce01f88a2845ebdd731d1a481e3ea0b7086cad8095f");
}
