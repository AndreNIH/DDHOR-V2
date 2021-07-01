#pragma once
#include "../../../GDTypes/GJBaseGameLayer.h"

namespace HK {
	namespace GJGameLayer{
		void __fastcall pushButton(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch);
		void __fastcall releaseButton(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch);
		void memInit();
	}
}
