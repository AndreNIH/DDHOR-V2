#pragma once
//Shared-Thread Input/Output

#include <thread>
#include <mutex>
#include <queue>
#include <optional>
#include <Windows.h>

struct KBE{
    const char vKeyCode;
    bool keyPressed;
};

class STIO{
private:
    std::mutex m_lock;
    std::queue<KBE> m_keyCodes;

    STIO(const STIO&){};
    STIO(){};
public:

    void addMsg(KBE msg);
    std::optional<KBE>fetchMsg();
    
    static STIO& get();
    
    
};