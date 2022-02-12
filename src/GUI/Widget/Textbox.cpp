#include "Textbox.h"
#include <ErrorHandling/Logger.h>
#include <gsl-lite.hpp>
namespace widget{

    bool Textbox::initTextbox(gd::CCTextInputNode* textInput, extension::CCScale9Sprite* background){
        if(!CCNode::init()) return false;
        _textInput = textInput;
        _background = _background;
        addChild(background);
        addChild(textInput);
        return true;
    }

    Textbox* Textbox::create(gd::CCTextInputNode* textInput, extension::CCScale9Sprite* background){
        auto obj = new Textbox();
        if(!obj || !obj->initTextbox(textInput, background)){
            CC_SAFE_DELETE(obj);
        }
        return obj;
    }

    gd::CCTextInputNode* Textbox::getTextInput(){
        return _textInput;
    }

    Textbox::operator gd::CCTextInputNode*(){
        return getTextInput();
    }


    void TextboxBuilder::setSize(float width, float height){
        _targetWidth  = width;
        _targetHeight = height;
    }

    void TextboxBuilder::setFont(const std::string& font){
        _font = font;
    }

    void TextboxBuilder::setCaption(const std::string& caption){
        _caption = caption;
    }

    void TextboxBuilder::setBackground(const std::string& backgroundFile, GLubyte opacity){
        _backgroundFile=backgroundFile;
        _opacity = opacity;
    }

    Textbox* TextboxBuilder::createTextInput(CCObject* object){
        try{
            auto in = gsl::make_not_null(gd::CCTextInputNode::create(
                        _caption.value().c_str(), 
                        object, 
                        _font.value().c_str(), 
                        _targetWidth.value(),
                        _targetHeight.value()));

            CCSize targetSize = {_targetWidth.value(), _targetHeight.value()};
            auto bg = gsl::make_not_null(extension::CCScale9Sprite::create(_backgroundFile.value().c_str(),{ 0,0, 40, 40 }));
            bg->setOpacity(_opacity);
            bg->setContentSize(targetSize);
            auto textbox = gsl::make_not_null(Textbox::create(in, bg));
            textbox->setContentSize(targetSize);
            return textbox;

        }catch(const std::bad_optional_access& ex){
            LOG_EXCEPTION(ex);
            return nullptr;
        }catch(const gsl::fail_fast& ex){
            LOG_EXCEPTION(ex);
            return nullptr;
        }
    }
}