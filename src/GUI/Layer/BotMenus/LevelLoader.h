#pragma once
#include <memory>
#include <cocos2d.h>
#include <functional>

using namespace cocos2d;
class LoaderWrapper{
private:
    using MethodT = void(CCObject*, CCObject*);
    CCObject* _context=nullptr;
    std::function<MethodT> _delegateMethod;    
public:
    LoaderWrapper(cocos2d::CCObject* loaderInstance, uint32_t loaderMethodAddr);
    void invoke();
};

class LevelLoader{
private:
    std::shared_ptr<LoaderWrapper> _loader;
public:
    void bindContext(std::shared_ptr<LoaderWrapper>&& loaderContext);
    void bindContext(const std::shared_ptr<LoaderWrapper>& loaderContext);
    void loadLevel();
};

