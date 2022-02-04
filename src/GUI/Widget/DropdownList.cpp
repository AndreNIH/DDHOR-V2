#include "DropdownList.h"
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>
#include <gsl/gsl-lite.hpp>
#include "DropdownItem.h"

namespace widget{

    void DropdownList::add(const std::string& element){
        spdlog::debug("DropdownList::add '{}'", element);
        auto item = DropdownItem::create(element,_elementSize, this, menu_selector(DropdownList::onItemSelected));
        if(item) _drawableElements.addObject(item);
    }

    void DropdownList::refresh(){
        spdlog::debug("DropdownList refresh requested");
        CCMenu::removeAllChildren();
        for(int windowOffset=0;windowOffset < _maxDisplayItems; windowOffset++){
            if(_displayPosition+windowOffset >= _drawableElements.count()) break;
            auto item = _drawableElements.objectAtIndex(_displayPosition+ windowOffset);
            CCMenu::addChild(reinterpret_cast<CCMenuItemSprite*>(item));
        }
        CCMenu::alignItemsVerticallyWithPadding(2);
    }

    void DropdownList::setSize(const CCSize& size){
        spdlog::debug("DropdownList resize requested");
        _elementSize=size;
        CCObject* element;
        CCARRAY_FOREACH(&_drawableElements, element){
            auto e = reinterpret_cast<DropdownItem*>(element);
            e->setContentSize(size);
        }
        refresh();
    };

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
}