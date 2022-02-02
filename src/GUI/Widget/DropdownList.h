#pragma once
#include <functional>
#include <string>
#include <cocos2d.h>
#include <cocos-ext.h>
#include <gd.h>

namespace widget{
    using namespace cocos2d;
    
    class DropdownItem : public CCMenuItem{
    private:
        extension::CCScale9Sprite* _bg = nullptr;
    public:
        bool init(const CCSize& size);
        void setContentSize(const CCSize& contentSize) override;
        
    };
    
    class DropdownList : public cocos2d::CCMenu, private gd::TextInputDelegate{
    private:
        typedef void(cocos2d::CCObject::* TextboxCallback)(gd::CCTextInputNode* sender);
        TextboxCallback* _cbTextEdited=nullptr;
        TextboxCallback* _cbTextOpened=nullptr;
        cocos2d::CCObject* _delegateInstance=nullptr;
        CCSize _elementSize;
        CCArray _drawableElements;
        unsigned int _maxDisplayItems = 5u;
        unsigned int _displayPosition = 0u;
        
        void onItemSelected(CCObject* sender){std::cout << "AMOGUSSSS!";};

        //CCMouseDelegate Method
        void scrollWheel(float x, float y) override{};

        //Forwarding methods for TextInputDelegate
        void textChanged(gd::CCTextInputNode*){};
        void textInputOpened(gd::CCTextInputNode*){};
    public:
        void add(const std::string& element);
        //void clear();
        //void setMaxDisplayItems(int maxItems);
        void refresh();
        //void displayList();
        //void hideList();

        /*void setPosition(const cocos2d::CCPoint& position) override;
        void setPositionX(float x) override;
        void setPositionY(float y) override;*/
        void setSize(const CCSize& size);
        CREATE_FUNC(DropdownList)
        //Callbacks()
        /*void bindToTextbox(gd::CCTextInputNode* textInput);
        void bindToReceiver(CCObject* reveiver);
        void setTextEditedCallback(TextboxCallback* editedCallback);
        void setTextOpenCallback(TextboxCallback* openedCallback);*/
        

    };
}