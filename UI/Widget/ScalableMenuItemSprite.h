#pragma once
#include <gd.h>


class ScalableMenuItemSprite : public cocos2d::CCMenuItemSprite{
private:
    float m_sizeMult = 1.25;
    float m_originalSize = 1.25;

public:
    virtual void selected() override;
	virtual void unselected() override;
	virtual void activate() override;
	
    virtual void setScale(float scale) override;
	
    static ScalableMenuItemSprite* create(CCNode *normalSprite, CCNode *selectedSprite, CCObject *target, cocos2d::SEL_MenuHandler selector);
	void setSizeMult(float multiplier) { m_sizeMult = multiplier; }

};