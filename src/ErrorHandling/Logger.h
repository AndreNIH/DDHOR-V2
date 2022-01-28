#pragma once 
#include <type_traits>
#include <string>
#include <spdlog/spdlog.h>
#include <fmt/format.h>

class Logger{
private:
    std::shared_ptr<spdlog::logger> _logger=nullptr;
    Logger();
public:
    static Logger& get(){
        static Logger l;
        return l;
    }

    spdlog::logger* log(){
        return _logger.get();
    }

    Logger(const Logger&)=delete;
    Logger(const Logger&&)=delete;
};



namespace{
    template <typename T>
    typename std::enable_if_t<!std::is_convertible_v<T, std::string>,std::string> 
    toString (T const & val){ 
        return std::to_string(val); 
    }
    
    std::string toString (std::string const & val){ 
        return val; 
    }
    
    template<typename... T>
    std::string stringify(const T&... val){
        std::string str;
        ((str += toString(val)), ...);
        return str;
    }

}

namespace li{
    template<typename ExceptionT, typename... Args>
    void log_exception_internal(
        const ExceptionT& exception, 
        const char* filename, 
        int line, 
        Args... additionalArgs)
    {
        std::string msg = "An exception of type '{}' has occured. " 
                          "Exception caught at line {} of file '{}'.\n";
        if constexpr(sizeof...(additionalArgs) > 0){
            msg += "Details: " + stringify(additionalArgs...);
        }
        auto errormsg = fmt::format(msg, typeid(ExceptionT).name(), line, filename);
        Logger::get().log()->error(errormsg);
        Logger::get().log()->flush();
    }
}

#define LOG_EXCEPTION(ExceptionObj, ...) li::log_exception_internal(ExceptionObj, __FILE__, __LINE__, __VA_ARGS__);
