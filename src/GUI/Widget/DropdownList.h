#pragma once
#include <functional>
#include <string>
#include <cocos2d.h>

namespace widget{
    
    class DropdownList : public cocos2d::CCMenu{
    private:
        typedef void(cocos2d::CCObject::* TextboxEdited)(std::string newText);
        typedef void(cocos2d::CCObject::* ItemSelected)(std::string newText);
        TextboxEdited* _cbTextEdited=nullptr;
        cocos2d::CCObject* _delegateInstance=nullptr;

        unsigned int _maxDisplayItems = 5u;
    public:
        void add(const std::string& element);
        void clear();
        void setMaxDisplayItems(int maxItems);
        void setPlaceholderText(const std::string& placeholder);

        void setPosition(const cocos2d::CCPoint& position) override;
        void setPositionX(float x) override;
        void setPositionY(float y) override;
        

        DropdownList(cocos2d::CCObject* delegate,  TextboxEdited* textEditedCb, ItemSelected* itemSelected );

    };
}