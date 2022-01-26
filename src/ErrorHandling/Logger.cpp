#include "Logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <Windows.h>

Logger::Logger() try{
        _logger = spdlog::basic_logger_mt("d-logger", "ddhor/logs/logfile.txt");
    }catch(const spdlog::spdlog_ex& ex){
        using namespace std::string_literals;
        const std::string msg = "Logger library initialization failure. Reason: "s + ex.what();
        MessageBoxA(NULL, msg.c_str(), "Spdlog Error", MB_ICONERROR);
    }