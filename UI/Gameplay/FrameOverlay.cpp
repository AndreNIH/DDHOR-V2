#include "FrameOverlayLayer.h"
#include <Engine/Manager.h>
#include <GameController.h>
using namespace cocos2d;

void FrameOverlayLayer::update(float dt){
    //Method only used to test whether to remove the layer from a node
    //Theoretically since whenever this layer is present CCScheduler is paused I shouldn't really need
    //to worry about testing if the Bot state is set to "Frozen"but I rather be explicit
    if(!GameController::getPaused())removeFromParentAndCleanup(true);
}

bool FrameOverlayLayer::init(){
    if(!CCLayer::init()) return false;
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto fbfLabel = CCLabelBMFont::create("Frame-by-frame mode","bigFont.fnt");
    fbfLabel->setScale(0.75);
    fbfLabel->setPositionX(5 + fbfLabel->getScaledContentSize().width/2);
    fbfLabel->setPositionY(winSize.height - 5 - fbfLabel->getScaledContentSize().height/2);
    addChild(fbfLabel);
    setTag(LAYER_IDENTIFIER);
    scheduleUpdate();
    return true;
}