#include "LevelLoader.h"
#include <ErrorChecking/TypeChecking.h>
#include <ErrorHandling/Logger.h>

LoaderWrapper::LoaderWrapper(CCObject* loaderInstance, uint32_t loaderMethodAddr){
    _context = loaderInstance;
    _delegateMethod = reinterpret_cast<MethodT>(loaderMethodAddr);
}


void LoaderWrapper::invoke(){
    try{
        rtc::notNull(_context);
        std::invoke(_delegateMethod, _context, nullptr);
    }catch(const DEX::NullException& ex){
        LOG_EXCEPTION(ex);
    }
}
