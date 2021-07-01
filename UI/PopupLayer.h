#pragma once
#include <cocos2d.h>
#include <cocos-ext.h>
#include <gd.h>

//This is an adapataion of HJFod's code
//Link: https://gist.github.com/HJfod/4d4e01131f016f0d2d842575ed896a08

class PopupLayer : public gd::FLAlertLayer {
protected:
    cocos2d::CCSize m_layerSize;
    virtual void setup() {};
    virtual bool init(float width, float height, const char* bgName = "GJ_square01.png");
    virtual void onClose(cocos2d::CCObject*);
    virtual void keyDown(cocos2d::enumKeyCodes key);
    virtual void keyBackClicked() override;
    void registerWithTouchDispatcher() override;

    void removeCloseBtn() { m_pButtonMenu->setVisible(false); }
        

};