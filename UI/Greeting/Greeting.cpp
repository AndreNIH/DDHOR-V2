#include "Greeting.h"
#include <cocos-ext.h>
using namespace cocos2d;
void GreetingLayer::removeCallback(){
    stopAllActions();
    removeFromParentAndCleanup(true);
}

void GreetingLayer::setOpacity(GLubyte opacity){
	CCObject* child;
	CCARRAY_FOREACH(CCLayer::getChildren(), child){
		CCNode* pNode = (CCNode*)child;
		cocos2d::CCRGBAProtocol* pRGBAProtocol = dynamic_cast<cocos2d::CCRGBAProtocol*>(pNode);
		if (pRGBAProtocol) pRGBAProtocol->setOpacity(opacity);
	};
}

bool GreetingLayer::init(){
    if(!CCLayer::init()) return false;
    CCSize winSize =  CCDirector::sharedDirector()->getWinSize();
    CCSize widgetsSize = {winSize.width * 0.4f, winSize.height * 0.15f};
    
    auto tint = extension::CCScale9Sprite::create("square02_small.png", { 0,0, 40, 40 });
    tint->setContentSize(widgetsSize);
    tint->setOpacity(100);
    tint->setPosition(winSize.width/2,winSize.height/2);
    addChild(tint);
    
    auto text = CCLabelBMFont::create("DDHOR Loaded", "bigFont.fnt", widgetsSize.width);
    text->setPosition(winSize.width/2, winSize.height/2);
    text->setScale(0.8f);
    addChild(text);

    auto actions = CCArray::create();
    actions->addObject(CCFadeOut::create(1));
    actions->addObject(CCCallFunc::create(this, callfunc_selector(GreetingLayer::removeCallback)));
    runAction(CCSequence::create(actions));
    return true;
}