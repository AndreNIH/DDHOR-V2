#pragma once
#include <Windows.h>

namespace WHK{
    LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);
    void init(DWORD mainThreadId);
    void release();
}

