#include "ScalableMenuItemSprite.h"

void ScalableMenuItemSprite::selected(){
	CCMenuItemSprite::selected();
	auto resize = cocos2d::CCScaleTo::create(0.3, m_sizeMult * m_originalSize);
	auto bounce = cocos2d::CCEaseBounceOut::create(resize);
	this->runAction(bounce);
}

void ScalableMenuItemSprite::unselected(){
	CCMenuItemSprite::unselected();
	this->stopAllActions();
	auto resize = cocos2d::CCScaleTo::create(0.3, m_originalSize);
	auto bounce = cocos2d::CCEaseBounceOut::create(resize);
	this->runAction(bounce);
}

void ScalableMenuItemSprite::activate () {
	CCMenuItemSprite::activate();
	this->stopAllActions();
	this->setScale(m_originalSize);
}

void ScalableMenuItemSprite::setScale(float scale) {
	m_originalSize = scale;
	CCMenuItemSprite::setScale(scale);	
}

ScalableMenuItemSprite* ScalableMenuItemSprite::create(CCNode *normalSprite, CCNode *selectedSprite, CCObject *target, cocos2d::SEL_MenuHandler selector){
	auto spriteItem = new ScalableMenuItemSprite;
	if (spriteItem && spriteItem->initWithNormalSprite(normalSprite, selectedSprite, nullptr, target, selector)) 
		spriteItem->autorelease();
	else {
		delete spriteItem;
		spriteItem = nullptr;
	}
	return spriteItem;

}