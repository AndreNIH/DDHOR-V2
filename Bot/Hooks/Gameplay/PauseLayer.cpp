#include "PauseLayer.h"
#include <Hooks/HookManger.h>
#include <Engine/Manager.h>
#include <Speedhack.h>
#include <GameController.h>
#include <gd.h>
using namespace cocos2d;
constexpr int MENU_TAG = 505;
constexpr int BTN_TAG  = 506;
class StopRecordingBtn : public CCNode{
private:
    void finalize(){
        GameController::setPaused(false);
		GameController::setSpeed(1.0);
		GameController::commit();
		auto name = Bot::get().config().getMacroName();
		Bot::get().serialize(name);
		Bot::get().setState(Bot::State::Idle);

        auto menu = reinterpret_cast<CCMenu*>(getChildByTag(MENU_TAG));
        menu->removeChildByTag(BTN_TAG);
        menu->alignItemsHorizontallyWithPadding(20.0); //this can also be 15 according to a game variable
    }

public:
    
    void onStop(CCObject* extra){ 
        //Add animation code later
        finalize();
    }
};


bool __fastcall HK::PauseLayer::init(void* self){
    typedef bool(__thiscall* ret)(void*);
    bool retval = HookManager::get().getFunctionPtr<ret>("c477c295f77e4873aa3341ead774cf8a85028e4e25a67ecb81337b37e5123b9f")(self);
     GameController::suspend();
    if(Bot::get().getState() == Bot::State::Recording) {
        auto menu = dynamic_cast<CCMenu*>(reinterpret_cast<CCLayer*>(self)->getChildren()->objectAtIndex(8));
        if(menu != nullptr){
            menu->setTag(505);
            auto stopSprite =  CCSprite::createWithSpriteFrameName("D2B_StopBtn_001.png");
            auto stopBtn = gd::CCMenuItemSpriteExtra::create(stopSprite, reinterpret_cast<CCObject*>(self), menu_selector(StopRecordingBtn::onStop));
            stopBtn->setTag(BTN_TAG);
            menu->addChild(stopBtn);
            menu->alignItemsHorizontallyWithPadding(20.0); //this can also be 15 according to a game variable
        }

    }
    return retval;

}

void __fastcall HK::PauseLayer::onResume(void* self, int edx, void* arg){
    typedef void(__thiscall* ret)(void*, void*);
    GameController::commit();
    HookManager::get().getFunctionPtr<ret>("670e627fc953c42b8b9fe3fc343828449d406f0e5b25ea8850538ce678ad7dd4")(self,arg);
}

void __fastcall HK::PauseLayer::onRestart(void* self, int edx, void* arg){
    typedef void(__thiscall* ret)(void*, void*);
    GameController::commit();
    HookManager::get().getFunctionPtr<ret>("71734f58ac860aa0ded45e9850bb8f40c50713d99a7887029bde9d6b25535116")(self,arg);
}

void HK::PauseLayer::memInit(){
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
    HookManager::get().addHook("c477c295f77e4873aa3341ead774cf8a85028e4e25a67ecb81337b37e5123b9f",base+0x168D0,PauseLayer::init); ///hooked init in combinatio of other hooks crashes the editor
    HookManager::get().addHook("670e627fc953c42b8b9fe3fc343828449d406f0e5b25ea8850538ce678ad7dd4",base+0x1E5FA0,PauseLayer::onResume);
    HookManager::get().addHook("71734f58ac860aa0ded45e9850bb8f40c50713d99a7887029bde9d6b25535116",base+0x1E6040,PauseLayer::onRestart);
}