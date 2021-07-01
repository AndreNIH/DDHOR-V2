#include "Speedhack.h"
#include <Windows.h>
#include <minhook/MinHook.h>
#include <iostream>

namespace int_speedhack{
    void* QPC = nullptr;
    void* GTC = nullptr;
    void* GTC_64 = nullptr;
}

namespace int_win32{
    void** QPC = nullptr;
    void** GTC = nullptr;
    void** GTC_64 = nullptr;
}

void(__stdcall* InitializeSpeedhack)(float speed) = nullptr;
float gSpeed = 1.0f;

void Speedhack::setSpeed(float speed){
    if(InitializeSpeedhack != nullptr) {
        gSpeed = speed;
        InitializeSpeedhack(speed);
    }
}

float Speedhack::getSpeed(){
    return gSpeed;
}


bool Speedhack::init(){
    HMODULE speedhack = LoadLibraryA("speedhack-i386.dll");
    HMODULE kernel = GetModuleHandleA("kernel32.dll");
    if(speedhack == NULL) return false;
    int_speedhack::QPC = GetProcAddress(speedhack, "speedhackversion_QueryPerformanceCounter");
    int_speedhack::GTC = GetProcAddress(speedhack, "speedhackversion_GetTickCount");
    int_speedhack::GTC_64 = GetProcAddress(speedhack, "speedhackversion_GetTickCount64");
    int_win32::QPC = reinterpret_cast<void**>(GetProcAddress(speedhack, "realQueryPerformanceCounter"));
    int_win32::GTC = reinterpret_cast<void**>(GetProcAddress(speedhack, "realGetTickCount"));
    int_win32::GTC_64 = reinterpret_cast<void**>(GetProcAddress(speedhack, "realGetTickCount64"));

    InitializeSpeedhack = reinterpret_cast<decltype(InitializeSpeedhack)>(GetProcAddress(speedhack, "InitializeSpeedhack"));

    void* qpc = GetProcAddress(kernel, "QueryPerformanceCounter");
    void* gtc = GetProcAddress(kernel, "GetTickCount");
    void* gtc_64 = GetProcAddress(kernel, "GetTickCount64");
    MH_CreateHook(qpc, int_speedhack::QPC, int_win32::QPC);
    MH_CreateHook(gtc, int_speedhack::GTC, int_win32::GTC);
    MH_CreateHook(gtc_64, int_speedhack::GTC, int_win32::GTC_64);
    MH_QueueEnableHook(qpc);
    MH_QueueEnableHook(gtc);
    MH_QueueEnableHook(gtc_64);
    MH_ApplyQueued();
    return true;
}

void Speedhack::uninit(){
    HMODULE kernel = GetModuleHandleA("kernel32.dll");
    
    void* qpc = GetProcAddress(kernel, "QueryPerformanceCounter");
    void* gtc = GetProcAddress(kernel, "GetTickCount");
    void* gtc_64 = GetProcAddress(kernel, "GetTickCount64");
    MH_RemoveHook(qpc);
    MH_RemoveHook(gtc);
    MH_RemoveHook(gtc_64);
    FreeLibrary(GetModuleHandleA("speedhack-i386.dll"));
}