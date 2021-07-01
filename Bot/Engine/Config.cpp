#include "Config.h"
#include <Windows.h>
#include <iostream>

bool ConfigRobProxy::getGameVariable(const std::string& key) const{
    bool val = gmGameVariable(gmInstance, key.c_str());
    return val;
} 

ConfigRobProxy::ConfigRobProxy(){
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
    gmInstance = reinterpret_cast<void*(__cdecl*)()>(base + 0xC4A50)();
    gmGameVariable = reinterpret_cast<decltype(gmGameVariable)>(base+0xC9D30);
}

BotConfiguration::BotConfiguration(){
    m_suspendIO = true;
    
}