#pragma once
#include <gd.h>


/*class PopupLayer : public gd::FLAlertLayer {
protected:
    cocos2d::CCSize m_layerSize;
    bool init(float width, float height, const char* bgName = "GJ_square01.png");
    void onClose(cocos2d::CCObject*);
    void keyDown(cocos2d::enumKeyCodes key);
    void keyBackClicked();
    void registerWithTouchDispatcher();
    void removeCloseBtn() { m_pButtonMenu->setVisible(false); 
    
    virtual void setup() {}
};*/

using namespace cocos2d;

class PopupLayer : public gd::FLAlertLayer{
protected:
    const CCSize _layerDimensions;
    const std::string _backgroundImage;
private:
    void enableLayerInput();
    void onClose(CCObject*);
    void keyDown(enumKeyCodes key) override final;
    void keyBackClicked() override final;
    void registerWithTouchDispatcher() override;
protected:
    
    virtual bool setup()=0;

public:
    virtual bool init() override final;
    virtual ~PopupLayer();
    PopupLayer(const CCSize& dimension, const std::string& background);
}; 