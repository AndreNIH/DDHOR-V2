#include "DropdownList.h"
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>
#include <gsl/gsl-lite.hpp>
#include "DropdownItem.h"

namespace widget{
    void DropdownList::setMaxDisplayItems(int maxItems){
        _maxDisplayItems = maxItems;
    }

    void DropdownList::add(const std::string& element){
        spdlog::debug("DropdownList::add '{}'", element);
        auto item = DropdownItem::create(element,_elementSize, this, menu_selector(DropdownList::onItemSelected));
        if(item) _drawableElements.addObject(item);
    }
    void DropdownList::clear(){
        spdlog::debug("DropdownList::clear requested");
        _drawableElements.removeAllObjects();
        removeAllChildren();
    }

    void DropdownList::refresh(){
        spdlog::debug("DropdownList::refresh requested");
        CCMenu::removeAllChildren();
        for(int windowOffset=0;windowOffset < _maxDisplayItems; windowOffset++){
            if(_displayPosition+windowOffset >= _drawableElements.count()) break;
            auto item = _drawableElements.objectAtIndex(_displayPosition+ windowOffset);
            CCMenu::addChild(reinterpret_cast<CCMenuItemSprite*>(item));
        }
        CCMenu::alignItemsVerticallyWithPadding(m_padding);
    }

    void DropdownList::setSize(const CCSize& size){
        spdlog::debug("DropdownList::resize requested: Size({},{})" ,size.width, size.height);
        _elementSize=size;
        CCObject* element;
        CCARRAY_FOREACH(&_drawableElements, element){
            auto e = reinterpret_cast<DropdownItem*>(element);
            e->setContentSize(size);
        }
    };

    const CCSize& DropdownList::getContentSize() const{
        CCObject* object=nullptr;
        CCSize contentSize=_elementSize;
        contentSize.height *= CCMenu::getChildrenCount();
        contentSize.height += CCMenu::getChildrenCount() * m_padding;
        return contentSize;
    }

    DropdownList* DropdownList::create(CCSize& size){
        DropdownList* instance = new DropdownList;
        if(instance && instance->init()) instance->autorelease();
        else CC_SAFE_DELETE(instance);
        instance->setSize(size);
        return instance;
    }

    DropdownList* DropdownList::create(){
        DropdownList* instance = new DropdownList;
        if(instance && instance->init()) instance->autorelease();
        else CC_SAFE_DELETE(instance);
        return instance;
    }

    //Callbacks

    void DropdownList::bindToTextbox(gd::CCTextInputNode* textInput){
        spdlog::trace("bindToTextbox, Unimplemented method");
    }

    void DropdownList::bindTextEditedCallback(TextboxCallback* editedCallback){
        spdlog::trace("bindTextEditedCallback, Unimplemented method");
    }

    void DropdownList::bindTextOpenCallback(TextboxCallback* openedCallback){
        spdlog::trace("bindTextOpenCallback, Unimplemented method");
    }

    void DropdownList::bindTextboxCloseCallback(TextboxCallback* closedCallback){
        spdlog::trace("bindTextboxCloseCallback, UIM");
    }
}