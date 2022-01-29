#pragma once
#include <memory>
#include <cocos2d.h>
#include <functional>

using namespace cocos2d;
class LoaderWrapper{
private:
    typedef void (__thiscall* MethodT)(CCObject*, CCObject*);
    CCObject* _context=nullptr;
    MethodT   _delegateMethod=nullptr;    
public:
    LoaderWrapper(cocos2d::CCObject* loaderInstance, uint32_t loaderMethodAddr);
    void invoke();
};
