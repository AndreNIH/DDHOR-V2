#pragma once
#include <cocos2d.h>


namespace HK {
	namespace LevelInfoLayer {
		bool __fastcall init(cocos2d::CCLayer* self,int edx, void* GJGameLevel);
		void memInit();
	}

	namespace EditLevelLayer {
		bool __fastcall init(cocos2d::CCLayer* self, int edx, void* GJGameLevel);
		void memInit();
	}
}


