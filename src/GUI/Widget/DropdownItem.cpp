#include"DropdownItem.h"
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>
#include <gsl/gsl-lite.hpp>

namespace widget{
    bool DropdownItem::initWithSize(const std::string& labelText,const CCSize& size, CCObject* target, SEL_MenuHandler callback){
        try{
            if(!initWithTarget(target, callback)) return false;
            auto background = gsl::not_null(extension::CCScale9Sprite::create("square02_small_white.png"));
            auto label = gsl::not_null(CCLabelBMFont::create(labelText.c_str(), "chatFont.fnt"));  
            _label=label;
            _bg=background;

            setContentSize(size);
            
            background->setAnchorPoint({0,0});
            label->setScale(0.5);
            label->setColor(ccBLACK);
            label->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
            label->setAnchorPoint({0.5,-0.5});
            label->setPositionX(background->getContentSize().width/2);
            addChild(background);
            addChild(label);
            return true;
        }catch(const gsl::fail_fast& ex){
            LOG_EXCEPTION(ex);
            return false;
        }

    }

    void DropdownItem::setContentSize(const CCSize& contentSize){
        CCMenuItem::setContentSize(contentSize);
        auto background = gsl::make_not_null(_bg);
        auto label = gsl::make_not_null(_label);
        background->setContentSize(contentSize);
        label->setPositionX(background->getContentSize().width/2);
    }

    DropdownItem* DropdownItem::create(const std::string& labelText, const CCSize& size, CCObject* target, SEL_MenuHandler callback){
        DropdownItem* instance = new DropdownItem;
        if(instance && instance->initWithSize(labelText, size, target, callback)){
            instance->autorelease();
        }else{
            CC_SAFE_DELETE(instance);
        }
        return instance;
    }



}