#include "LevelLoading.h"
#include <Hooks/HookManger.h>
#include "../UI/Widget/LoadingButton.h"
using namespace cocos2d;

typedef bool(__thiscall* ret)(void*, void*);
bool __fastcall HK::LevelInfoLayer::init(CCLayer* self, int edx, void* GJGameLevel){
    
    HookManager::get().getFunctionPtr<ret>("ff7bd9d9f66cfadea0bcba17ce450a5bab73c96bda92666f7bdd5a9f8cffe7c8")(self, GJGameLevel);
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
    CCObject* layerChild;
    CCARRAY_FOREACH(self->getChildren(), layerChild) {
        auto menu = dynamic_cast<CCMenu*>(layerChild);
        if (menu == nullptr) continue;
        if (menu->getChildrenCount() != 1) continue;
        if (menu->getZOrder() != 3) continue;
        
        auto item = reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(0));
        auto btn = GUI::Widget::LoadingButton::create(self);
        btn->setNewLoaderContext( self, base + 0x179730 );
        
        btn->setPosition(item->getPosition());
        btn->setZOrder(3);
        menu->removeAllChildren();
        menu->addChild(btn);
    }
	return true;
}

bool __fastcall HK::EditLevelLayer::init(CCLayer* self, int edx, void* GJGameLevel){
    HookManager::get().getFunctionPtr<ret>("6f4e14d25afc1fcd4705b1515f716662869cd74d3d90cbefc3285d1615cdc46d")(self, GJGameLevel);
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
    CCObject* layerChild;
    CCARRAY_FOREACH(self->getChildren(), layerChild) {
        auto menu = dynamic_cast<CCMenu*>(layerChild);
        if (menu == nullptr) continue;
        if (menu->getChildrenCount() != 3) continue;
        auto item = reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(1));
        auto btn  = GUI::Widget::LoadingButton::create(self);
        btn->setNewLoaderContext(self, base + 0x71700);
        
        btn->setPosition(item->getPosition());
        menu->addChild(btn);
        menu->removeChild(item, true);
    }
    return true;
}

//Initializers
void HK::LevelInfoLayer::memInit(){
	uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
	HookManager::get().addHook("ff7bd9d9f66cfadea0bcba17ce450a5bab73c96bda92666f7bdd5a9f8cffe7c8", base + 0x175DF0, LevelInfoLayer::init);
}

void HK::EditLevelLayer::memInit() {
	uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
	HookManager::get().addHook("6f4e14d25afc1fcd4705b1515f716662869cd74d3d90cbefc3285d1615cdc46d", base + 0x6F5D0, EditLevelLayer::init);
}
