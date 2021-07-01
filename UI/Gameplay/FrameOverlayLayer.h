#pragma once
#include <cocos2d.h>

class FrameOverlayLayer :public cocos2d::CCLayer {
public:
    static const int LAYER_IDENTIFIER = 97139;
    bool init() override;
    void update(float dt);
    CREATE_FUNC(FrameOverlayLayer);
};