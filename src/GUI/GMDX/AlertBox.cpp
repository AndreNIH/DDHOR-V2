#include "AlertBox.h"
namespace gmdx{

    void AlertBox::setTitle(const std::string& title){
        _title = title;
    }

    void AlertBox::setContent(const std::string& content){
        _content = content;
    }

    void AlertBox::setSize(float size){
        _size = size;
    }

    void AlertBox::setButtonText(const std::string& b1)
    {
        _button1 = b1;
    }

    void AlertBox::setButtonText(const std::string& b1, const std::string& b2){
        _button1 = b1;
        _button2 = b2;
    }

    void AlertBox::addDelegate(gd::FLAlertLayerProtocol* delegate){
        _delegate = delegate;
    }

    void AlertBox::show(){
        const char* b1 = _button1.c_str();
        const char* b2 = _button2.has_value()  ? _button2.value().c_str() : nullptr;
        gd::FLAlertLayer* alert = _size.has_value()
            ? gd::FLAlertLayer::create(_delegate, _title.c_str(),b1,b2,_size.value(),_content)
            : gd::FLAlertLayer::create(_delegate, _title.c_str(),b1,b2,_content);
        alert->show();        
   }
}