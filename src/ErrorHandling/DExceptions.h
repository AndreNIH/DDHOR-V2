#pragma once
#include <stdexcept>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <type_traits>
#include <Windows.h>
namespace DEX{
    class NullException: public std::runtime_error{
    public:
        using BaseEx = std::runtime_error;
        explicit NullException(const std::string& message) : BaseEx(message.c_str()) {}
        explicit NullException(const char* message) : BaseEx(message) {}
    };

    class IllegalOperation: public std::runtime_error{
    public:
        using BaseEx = std::runtime_error;
        explicit IllegalOperation(const std::string& message) : BaseEx(message.c_str()) {}
        explicit IllegalOperation(const char* message) : BaseEx(message) {}
    };

    class DeserializerError: public std::runtime_error{
    public:
        using BaseEx = std::runtime_error;
        explicit DeserializerError(const std::string& message) : BaseEx(message.c_str()) {}
        explicit DeserializerError(const char* message) : BaseEx(message) {}
    };

    class SerializerError: public std::runtime_error{
    public:
        using BaseEx = std::runtime_error;
        explicit SerializerError(const std::string& message) : BaseEx(message.c_str()) {}
        explicit SerializerError(const char* message) : BaseEx(message) {}
    };

    class FileNotFound : public std::runtime_error{
    public:
        using BaseEx = std::runtime_error;
        explicit FileNotFound(const std::string& message) : BaseEx(message.c_str()) {}
        explicit FileNotFound(const char* message) : BaseEx(message) {}
    };
}


