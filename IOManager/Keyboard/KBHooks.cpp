#include "KBHooks.h"
#include <iostream>
#include <bitset>
#include "../STIO.h"

HOOKPROC kbHookProc = nullptr;
HHOOK    hHook = nullptr;


LRESULT CALLBACK WHK::KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam){
    if(nCode >= 0){
        bool keyReleased = !std::bitset<32>((uint32_t)lParam).test(31);
        STIO::get().addMsg({static_cast<char>(wParam),keyReleased});
    }
    return CallNextHookEx(hHook,nCode,wParam,lParam);
}

void WHK::init(DWORD mainThreadId){
    kbHookProc = WHK::KeyboardHook;
    hHook = SetWindowsHookExA(WH_KEYBOARD,kbHookProc,NULL, mainThreadId);
}

void WHK::release(){
    UnhookWindowsHookEx(hHook);
}