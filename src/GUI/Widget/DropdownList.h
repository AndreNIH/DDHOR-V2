#pragma once
#include <functional>
#include <string>
#include <cocos2d.h>
#include <cocos-ext.h>
#include <gd.h>

namespace widget{
    using namespace cocos2d;
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
        const float m_padding = 2.0f;
        
        void onItemSelected(CCObject* sender){std::cout << "AMOGUSSSS!";};

        //CCMouseDelegate Method
        void scrollWheel(float x, float y) override{};

        //Forwarding methods for TextInputDelegate
        void textChanged(gd::CCTextInputNode*) override{};
        void textInputOpened(gd::CCTextInputNode*) override{};
        void textInputClosed(gd::CCTextInputNode*) override{};
    public:
        
        void setMaxDisplayItems(int maxItems);
        
        void add(const std::string& element);
        void clear();
        void refresh();

        void setSize(const CCSize& size);
        const CCSize& getContentSize() const override;
        static DropdownList* create(CCSize& size);
        static DropdownList* create();
        
        //Callbacks
        void bindToTextbox(gd::CCTextInputNode* textInput);
        void bindTextEditedCallback(TextboxCallback* editedCallback);
        void bindTextOpenCallback(TextboxCallback* openedCallback);
        void bindTextboxCloseCallback(TextboxCallback* closedCallback);
        
        

    };
}