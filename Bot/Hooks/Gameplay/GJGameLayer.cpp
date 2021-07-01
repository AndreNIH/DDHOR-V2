#include "GJGameLayer.h"
#include <Hooks/HookManger.h>
#include <Engine/Manager.h>
#include "../UI/Gameplay/SyncLayer.h"
bool inputBelongsToP1(GT::GJBaseGameLayer* pl, bool leftTouch) {
	bool is2PM = pl->effectManager->is2PMode;
	if (!is2PM) return true;
	else if (is2PM && !pl->isDualMode) return true;
	else if (is2PM && pl->isDualMode && leftTouch) return true;
	return false;
}

typedef void(__thiscall* btnFunction)(void*, int, bool);
void __fastcall HK::GJGameLayer::pushButton(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch){
	auto pOriginal = HookManager::get().getFunctionPtr<btnFunction>("1b92b7eb72f93e4fcdc80a3930e784961d54f8e7eb49cfb67738f9485b4e6f9d");
	float x = self->player1->XPos;
	
	if (Bot::get().getState() == Bot::State::Recording) {
		//if(x == 0.0f) return;
		auto layer = reinterpret_cast<cocos2d::CCLayer*>(self);
		auto sync = reinterpret_cast<SyncLayer*>(layer->getChildByTag(SyncLayer::TAG));
		if (inputBelongsToP1(self, leftTouch)){
			Bot::get().recorder().first.addInput(x, Act::PUSH);
			sync->reportForP1(Act::PUSH);
		}
		else{
			Bot::get().recorder().second.addInput(x, Act::PUSH);
			sync->reportForP2(Act::PUSH);
		}
	}
	pOriginal(self, a1, leftTouch);
}

void __fastcall HK::GJGameLayer::releaseButton(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch){
	auto pOriginal = HookManager::get().getFunctionPtr<btnFunction>("cb5a1230ab8154e622c7ba3314c2918add7f6285e5a7324d700553d30af151f1");
	float x = self->player1->XPos;
	if (Bot::get().getState() == Bot::State::Recording) {
		//if(x == 0.0f) return;
		auto layer = reinterpret_cast<cocos2d::CCLayer*>(self);
		auto sync = reinterpret_cast<SyncLayer*>(layer->getChildByTag(SyncLayer::TAG));
		if (inputBelongsToP1(self, leftTouch)) {
			Bot::get().recorder().first.addInput(x, Act::RELEASE);
			sync->reportForP1(Act::RELEASE);
		}
		else{
			Bot::get().recorder().second.addInput(x, Act::RELEASE);
			sync->reportForP2(Act::RELEASE);
		}
	}
	pOriginal(self, a1, leftTouch);
}

void HK::GJGameLayer::memInit()
{
	uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
	HookManager::get().addHook("1b92b7eb72f93e4fcdc80a3930e784961d54f8e7eb49cfb67738f9485b4e6f9d",    base + 0x111500, pushButton);
	HookManager::get().addHook("cb5a1230ab8154e622c7ba3314c2918add7f6285e5a7324d700553d30af151f1", base + 0x111660, releaseButton);
}
