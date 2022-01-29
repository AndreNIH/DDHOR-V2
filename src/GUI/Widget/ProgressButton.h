#pragma once
#include <gd.h>
#include "../LevelLoader.h"
using namespace cocos2d;

class ProgressButton : public CCMenuItemSprite{
private:
    static const int MENULAYER_TAG = 1006;
    CCArray*  _loadingButtonSpriteFrames=nullptr;
    float     _sizeMult = 1.0f;
    std::shared_ptr<LoaderWrapper> _loader;

    CCSprite* getDefaultSprite();

    void onLoadLevel(CCObject* sender);
    void onBeginLoadingAnimation();
    void onEndLoadingAnimation();
    
    void restartButtonSprite();
    
    void selected() override;
	void unselected() override;
	void activate() override;
    
public:
    void setSizeMultiplier(float multiplier);
    void setLevelLoader(std::shared_ptr<LoaderWrapper>& loader);
    bool init() override;
    CREATE_FUNC(ProgressButton);
    virtual ~ProgressButton();
};