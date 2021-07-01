#pragma once
#include <cocos2d.h>

struct STLoad : public cocos2d::CCObject{
	
	static STLoad& get();
	static void loadResources();
	static void hookKeyboard();
	void invokeLoader(float dt);
	
	~STLoad();
};
