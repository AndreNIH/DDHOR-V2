// dllmain.cpp : Defines the entry point for the DLL application.
//#define WIN32_LEAN_AND_MEAN

#include <gd.h>
#include <minhook/MinHook.h>
#include "STLoad/STLoad.h"
#include "Hooks/LevelLoading/LevelLoading.h"
#include "Hooks/Gameplay/GJGameLayer.h"
#include "Hooks/Gameplay/PlayLayer.h"
#include "Hooks/Gameplay/UILayer.h"
#include "Hooks/Gameplay/CCScheduler.h"
#include "Hooks/Gameplay/PauseLayer.h"
#include "Hooks/Gameplay/GDFixes/Checkpoints.h"
#include "Hooks/Options/MoreOptionsLayer.h"
#include "Hooks/TextureLoading/GameManager.h"

#include "Cheats/Speedhack.h"
#include "Cheats/Bypass.h"

#include "Bot/Hooks/HookManger.h"
#include "Bot/Engine/Manager.h"
#include <filesystem>
__declspec(dllexport) const char* DDHORBOT_VERSION = "2.0.1";

void superInit() {
    //console
    /*AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);*/
    
    //create macro directory
    std::filesystem::create_directories("ddhor");

    //Dependencies
    MH_Initialize();
    gd::init();
    //Hooks
    HK::GJGameLayer::memInit();
    HK::PlayLayer::memInit();
    HK::UILayer::memInit();
    HK::LevelInfoLayer::memInit();
    HK::EditLevelLayer::memInit();
    HK::CCScheduler::memInit();
    HK::PauseLayer::memInit();
    HK::MoreOptionsLayer::memInit();
    HK::GameManager::memInit();
    
    //Fixes
    HK::PlayerObject::memInit();
    LoadLibraryA("gdpatch_01.dll");
    
    //Cheats
    Speedhack::init();
    Bypass::init();

    
    //Textures
    using namespace cocos2d;
    auto scheduler = cocos2d::CCDirector::sharedDirector()->getScheduler();
    scheduler->scheduleSelector(schedule_selector(STLoad::invokeLoader), &STLoad::get(), 0, false);

    MH_EnableHook(MH_ALL_HOOKS);
}

DWORD WINAPI main_thread(void* hModule) {
    superInit();
    return 0;
    /*std::cin.get();
    Speedhack::uninit();
    MH_Uninitialize();
    FreeConsole();
    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);*/

}


BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, main_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


