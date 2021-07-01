#pragma once
#include "../../../GDTypes/PlayLayer.h"
#include <cocos2d.h>
namespace HK {
	namespace PlayLayer {
		bool __fastcall init(GT::PlayLayer* self, int edx, void* gameLevel);
		void __fastcall update(GT::PlayLayer* self, int edx, float dt);
		void __fastcall resetLevel(GT::PlayLayer* self);
		void __fastcall levelComplete(GT::PlayLayer* self);
		void __fastcall onQuit(GT::PlayLayer* self);
		void __fastcall playEndAnimationToPos(GT::PlayLayer* self, int edx, cocos2d::CCPoint point);
		void memInit();
	}
}