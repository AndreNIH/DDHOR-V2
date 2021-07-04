#include "PlayLayer.h"
#include <Hooks/HookManger.h>
#include <Engine/Manager.h>
#include "../UI/Gameplay/SyncLayer.h"
#include "../UI/Gameplay/SpeedhackLayer.h"
#include <GameController.h>
//Due to efficiency reasons only look up the value of "update" once
typedef void(__thiscall* ret)(void*, float);
ret pUpdateOriginal = nullptr;

bool __fastcall HK::PlayLayer::init(GT::PlayLayer* self, int edx, void* gameLevel){
	typedef bool(__thiscall* ret)(void*, void*);
	void* pOriginal = HookManager::get().getFunctionPtrRaw("c5d4bc37c9094fa0963488664358b22348da987cb21f28c20960d37d26909780");
	bool retVal = reinterpret_cast<ret>(pOriginal)(self, gameLevel);
	
	if(Bot::get().getState() != Bot::State::Idle){
		MH_EnableHook(HookManager::get().getFunctionPtrRaw("c477c295f77e4873aa3341ead774cf8a85028e4e25a67ecb81337b37e5123b9f"));
		
		Bot::get().bindObject(self);
		cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0f/Bot::get().config().getFPS());

		auto sync = SyncLayer::create();
		sync->bindPlayLayer(self);
		sync->setTag(SyncLayer::TAG);
		reinterpret_cast<cocos2d::CCLayer*>(self)->addChild(sync, 5);
	}
	
	GameController::setPaused(false);
	GameController::setSpeed(1.0);
	Bot::get().config().setSuspendIO(false);
	return retVal;
}

void __fastcall HK::PlayLayer::update(GT::PlayLayer* self, int edx, float dt){
	auto& config = Bot::get().config();
	float newDt = !config.getNoDeltaOverride() ? 1.0 / config.getFPS() : dt;
	dt = Bot::get().getState() == Bot::State::Idle  ? dt : newDt;
	pUpdateOriginal(self, dt);
	if (Bot::get().getState() == Bot::State::Playing) {
		Bot::get().player().first.peform(self->player1->XPos);
		Bot::get().player().second.peform(self->player1->XPos);
	}
	
}

void __fastcall HK::PlayLayer::resetLevel(GT::PlayLayer* self){
	typedef void(__thiscall* ret)(void*);
	auto respawn = HookManager::get().getFunctionPtr<ret>("44d64426e029288cee9f53ca9e668e55ad40f26ee88334f5c284ba79ba5311c9");
	if (Bot::get().getState() == Bot::State::Recording) {
		typedef void(__thiscall* dpPtr)(void*,bool);
		auto layer = reinterpret_cast<cocos2d::CCLayer*>(self);
		auto sync = reinterpret_cast<SyncLayer*>(layer->getChildByTag(SyncLayer::TAG));
		//if-statement required, sync is nullptr when entering the level
		if(sync) {
			if(!self->player1->isDead){
				uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
				dpPtr kill = reinterpret_cast<dpPtr>(base + 0x1efaa0);
				kill(self->player1,false);
				kill(self->player2,false);
			}
			sync->show();
		}else respawn(self);
	}
	else if (Bot::get().getState() == Bot::State::Playing) {
		respawn(self);
		auto release = HookManager::get().getFunctionPtr<void(__thiscall*)(void*, int, bool)>("cb5a1230ab8154e622c7ba3314c2918add7f6285e5a7324d700553d30af151f1");
		release(self, 0, false);
		release(self, 0, true);
		auto& players = Bot::get().player();
		players.first.rewind(self->player1->XPos);
		players.second.rewind(self->player1->XPos);
	}
	else {
		respawn(self);
	}
}

void __fastcall HK::PlayLayer::levelComplete(GT::PlayLayer* self) {
	typedef void(__thiscall* ret)(void*);
	ret pOriginal = HookManager::get().getFunctionPtr<ret>("f084bddfcc35c8071489ebfce5770e8ce430b4e69657ae6642f0d7ec206b8df5");
	GameController::setPaused(false);
	GameController::setSpeed(1.0);
	GameController::commit();	

	if (Bot::get().getState() == Bot::State::Recording) {
		auto name = Bot::get().config().getMacroName();
		Bot::get().serialize(name);
		Bot::get().setState(Bot::State::Idle);
	}

	if(Bot::get().getState() == Bot::State::Playing){
		if(Bot::get().config().getSafemode()){
			PlayLayer::onQuit(self);
			return;
		}
	}
	
	pOriginal(self);
	Bot::get().config().setSuspendIO(false);
}


void __fastcall HK::PlayLayer::onQuit(GT::PlayLayer* self){
	typedef void(__thiscall* ret)(void*);
	ret pOriginal = HookManager::get().getFunctionPtr<ret>("a269f5b7611c1f2367f0856ce0c8147f0380e105a3e81b75a70b6da2fa971654");
	auto status = Bot::get().getState();
	
	if(status == Bot::State::Recording){
		const float size = cocos2d::CCDirector::sharedDirector()->getWinSize().width * 0.7;
		auto alert = gd::FLAlertLayer::create(
			nullptr,
			"Recording in progress",
			"Ok",
			nullptr,
			size,
			"You can't exit a level while you are recording. Save the macro before attempting to exit the level");
		alert->show();
		return;
	}
	else if(status == Bot::State::Playing){
		Bot::get().setState(Bot::State::Idle);
	}
	
	GameController::setPaused(false);
	GameController::setSpeed(1.0);
	GameController::commit();	
	Bot::get().config().setSuspendIO(true);
	pOriginal(self) ;
}

void __fastcall HK::PlayLayer::playEndAnimationToPos(GT::PlayLayer* self, int edx, cocos2d::CCPoint point){
	typedef void(__thiscall* ret)(void*, cocos2d::CCPoint);
	Bot::get().config().setSuspendIO(true);
	GameController::setPaused(false);
	GameController::setSpeed(1.0);
	GameController::commit();
		
	HookManager::get().getFunctionPtr<ret>("b08ad4243b1053dc8a07848cd3f14211a36e8529eaaaf3e1c9fc028f71283ce4")(self, point);
}


void HK::PlayLayer::memInit(){
	uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
	HookManager::get().addHook("c5d4bc37c9094fa0963488664358b22348da987cb21f28c20960d37d26909780", base + 0x1FB780, PlayLayer::init);
	HookManager::get().addHook("294c0bae7cbaba708b71f870ec6e65b59cf21d3e0eb3d306715a0046e9f8e3c0", base + 0x2029C0, PlayLayer::update);
	HookManager::get().addHook("44d64426e029288cee9f53ca9e668e55ad40f26ee88334f5c284ba79ba5311c9", base + 0x20BF00, PlayLayer::resetLevel);
	HookManager::get().addHook("f084bddfcc35c8071489ebfce5770e8ce430b4e69657ae6642f0d7ec206b8df5", base + 0x1FD3D0, PlayLayer::levelComplete);
	HookManager::get().addHook("a269f5b7611c1f2367f0856ce0c8147f0380e105a3e81b75a70b6da2fa971654", base + 0x20D810, PlayLayer::onQuit);
	HookManager::get().addHook("b08ad4243b1053dc8a07848cd3f14211a36e8529eaaaf3e1c9fc028f71283ce4", base + 0x1FF380, PlayLayer::playEndAnimationToPos);
	pUpdateOriginal = HookManager::get().getFunctionPtr<ret>("294c0bae7cbaba708b71f870ec6e65b59cf21d3e0eb3d306715a0046e9f8e3c0");
	
}
