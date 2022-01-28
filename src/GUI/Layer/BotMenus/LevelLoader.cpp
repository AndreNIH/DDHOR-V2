#include "LevelLoader.h"
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>

LoaderWrapper::LoaderWrapper(CCObject* loaderInstance, uint32_t loaderMethodAddr){
    _context = loaderInstance;
    _delegateMethod = reinterpret_cast<MethodT*>(loaderMethodAddr);
}


void LoaderWrapper::invoke(){
        try{
            rtc::notNull(_context);
            _delegateMethod(_context, nullptr);
        }catch(const DEX::NullException& ex){
            LOG_EXCEPTION(ex);
        }catch(const std::bad_function_call& ex){
            LOG_EXCEPTION(ex);
        }
    }

    void LevelLoader::bindContext(std::shared_ptr<LoaderWrapper>&& loaderContext){
        _loader = std::move(loaderContext);
    }

    void LevelLoader::bindContext(const std::shared_ptr<LoaderWrapper>& loaderContext){
        _loader = loaderContext;
    }

    void LevelLoader::loadLevel(){
        rtc::notNull(_loader);
        _loader->invoke();
    }
