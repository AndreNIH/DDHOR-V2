#pragma once
#include <ErrorHandling/DExceptions.h>
#include <typeinfo>
#include <fmt/format.h>
#include <memory>
namespace rtc{
    template<typename T>
    void notNull(const T* ptr){
        if(ptr == nullptr) {
            const std::string msg = "Failed rtc::notNull check. Pointer({}) was null";
            throw DEX::NullException{fmt::format(msg,typeid(ptr).name())};
        }
    }

    template<typename T>
    void notNull(const std::unique_ptr<T>& ptr) {
        notNull(ptr.get());
    }

    template<typename T>
    void notNull(const std::shared_ptr<T>& ptr) {
        notNull(ptr.get());
    }
}