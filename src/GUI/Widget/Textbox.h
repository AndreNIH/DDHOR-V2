#pragma once
#include <cocos2d.h>
#include <cocos-ext.h>
#include <gd.h>
#include <optional>

namespace widget{
    using namespace cocos2d;

    class Textbox : public CCNode{
    private:
        gd::CCTextInputNode* _textInput=nullptr;
        extension::CCScale9Sprite* _background=nullptr;
        
    public:

        bool initTextbox(gd::CCTextInputNode* textInput, extension::CCScale9Sprite* background);
        static Textbox* create(gd::CCTextInputNode* textInput, extension::CCScale9Sprite* background);
        gd::CCTextInputNode* getTextInput();
        operator gd::CCTextInputNode*();
    };

    class TextboxBuilder{
    private:
        std::optional<float> _targetWidth;
        std::optional<float> _targetHeight;
        std::optional<std::string> _font;
        std::optional<std::string> _caption;
        std::optional<std::string> _backgroundFile;
        GLubyte _opacity=255;

    public:
        void setSize(float width, float height);
        void setFont(const std::string& font);
        void setCaption(const std::string& caption);
        void setBackground(const std::string& backgroundFile, GLubyte opacity=255);
        Textbox* createTextInput(CCObject* object);
    };
}