#include "UILayer.h"
#include "../UI/Gameplay/SpeedhackLayer.h"
#include "../UI/Gameplay/FrameOverlayLayer.h"
#include "../HookManger.h"
#include <Engine/Manager.h>
using namespace cocos2d;

template<typename T>
inline T createFunc(int offs) {
	uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
	return reinterpret_cast<T>(base + offs);
}

void __fastcall HK::UILayer::keyDown(CCLayer* self, int edx, enumKeyCodes key){
	typedef void(__thiscall* ret)(void*, enumKeyCodes);
	auto pOriginal = HookManager::get().getFunctionPtr<ret>("257bb411ac4cb329d620ac62ebda7b170fe901746027375dc9077253d51cb563");
	
	
	pOriginal(self, key); //if i hook a key that noramlly modifies the scene, change this back to the bottom of the func
	if(Bot::get().config().getSuspendIO()) return;
	
	if (key == enumKeyCodes::KEY_C) {
		auto onPause = createFunc<void(__thiscall*)(void*, void*)>(0x25FAD0);
		auto scene = CCDirector::sharedDirector()->getRunningScene();
		onPause(self, nullptr);
		auto pauseLayer = scene->getChildren()->objectAtIndex(1);
		if(pauseLayer != nullptr){
			int index = scene->getChildren()->objectAtIndex(1)->getTag() == FrameOverlayLayer::LAYER_IDENTIFIER ? 2 : 1;
			CCLayer* pauseLayer = reinterpret_cast<CCLayer*>(scene->getChildren()->objectAtIndex(index));
			if (pauseLayer != nullptr) {
				pauseLayer->removeAllChildrenWithCleanup(true);
				pauseLayer->addChild(SpeedhackLayer::create(250, 125), 15);
			}
		}
	}
	
}

void HK::UILayer::memInit(){
	uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
	HookManager::get().addHook("257bb411ac4cb329d620ac62ebda7b170fe901746027375dc9077253d51cb563", base + 0x25F890, UILayer::keyDown);
}
