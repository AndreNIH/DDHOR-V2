#pragma once
#include <gd.h>
#include "../PopupLayer.h"
class SpeedhackLayer : public PopupLayer{
private:
    gd::CCTextInputNode* m_newSpeed = nullptr;
    cocos2d::CCLayer* m_pauseLayer = nullptr;
    float m_speed = 1.0f;
    bool m_shouldPauseOnResume = false;
    
    void onClose(cocos2d::CCObject* sender) override;
    void onUpdateSpeed(cocos2d::CCObject* sender);
public:
    void setup() override;
    void setPauseLayerPtr(cocos2d::CCLayer* layer) { m_pauseLayer = layer; }
    static SpeedhackLayer* create(float width, float height, const char* bgName = "GJ_square01.png");

    SpeedhackLayer();
    
};