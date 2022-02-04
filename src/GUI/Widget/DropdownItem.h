#pragma once
#include <string>
#include <cocos2d.h>
#include <cocos-ext.h>

namespace widget{
    using namespace cocos2d;
    
    class DropdownItem : public CCMenuItem{
    private:
        extension::CCScale9Sprite* _bg = nullptr;
        CCLabelBMFont* _label = nullptr;
        DropdownItem()=default;
    public:
        bool initWithSize(const std::string& label,const CCSize& size, CCObject* target, SEL_MenuHandler callback);
        void setContentSize(const CCSize& contentSize) override;
        static DropdownItem* create(const std::string& labelText, const CCSize& size, CCObject* target, SEL_MenuHandler callback);
    };
}