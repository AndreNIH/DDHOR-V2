#include "DropdownList.h"
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>
#include <gsl/pointers>
bool widget::DropdownItem::init(){
    try{
        auto background = gsl::not_null(extension::CCScale9Sprite::create("square02_small_white.png"));
        background->setContentSize({0,0});
        background->setAnchorPoint({0,0});
        auto label = gsl::not_null(CCLabelBMFont::create("", "chatFont.fnt"));  
        label->setScale(0.5);
        label->setColor(ccBLACK);
        label->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        label->setAnchorPoint({0,-0.5});
        label->setPositionX(background->getContentSize().width/2);
        
        
        
        return true;
    }catch(const DEX::NullException& ex){
        LOG_EXCEPTION(ex);
        return false;
    }

}


void widget::DropdownList::add(const std::string& element){
    //TODO: Erro cehcking
    auto bg = extension::CCScale9Sprite::create("square02_small_white.png");
    auto menuItem = CCMenuItemSprite::create(bg,bg,this, menu_selector(DropdownList::onItemSelected));
    rtc::notNull(menuItem);
    auto label =CCLabelBMFont::create(element.c_str(), "chatFont.fnt");
    label->setScale(0.5);
    label->setColor(ccBLACK);
    label->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    label->setAnchorPoint({0.5, -0.5});
    label->setPositionX(_elementSize.width / 2);

    bg->setContentSize(_elementSize);
    menuItem->setContentSize(_elementSize);
    menuItem->addChild(label);
    _drawableElements.addObject(menuItem);
}

void widget::DropdownList::refresh(){
    CCMenu::removeAllChildren();
    for(int windowOffset=0;windowOffset < _maxDisplayItems; windowOffset++){
        if(_displayPosition+windowOffset >= _drawableElements.count()) break;
        auto item = _drawableElements.objectAtIndex(_displayPosition+ windowOffset);
        CCMenu::addChild(reinterpret_cast<CCMenuItemSprite*>(item));
    }
    CCMenu::alignItemsVerticallyWithPadding(2);
}

void widget::DropdownList::setSize(const CCSize& size){
    _elementSize=size;
    CCObject* element;
    CCARRAY_FOREACH(&_drawableElements, element){
        auto e = reinterpret_cast<CCMenuItemSprite*>(element);
        auto c = e->getChildren()->objectAtIndex(0);
        e->setContentSize(size);
    }
    refresh();
};