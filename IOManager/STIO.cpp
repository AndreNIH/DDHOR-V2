#include "STIO.h"

void STIO::addMsg(KBE msg){
    std::lock_guard<std::mutex> lg(m_lock);
    m_keyCodes.push(msg);
}

std::optional<KBE> STIO::fetchMsg(){
    std::lock_guard<std::mutex> lg(m_lock);
    if(m_keyCodes.empty()) return std::nullopt;
    auto val = m_keyCodes.front();
    m_keyCodes.pop();
    return val;
}

STIO& STIO::get(){
    static STIO instance;
    return instance;
}