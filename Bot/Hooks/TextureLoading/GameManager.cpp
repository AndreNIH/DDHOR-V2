#include "GameManager.h"
#include "../STLoad/STLoad.h"
#include <Hooks/HookManger.h>
void __fastcall HK::GameManager::reloadAllStep5(void* self){
    HookManager::get().getFunctionPtr<void(__thiscall*)(void*)>("a7e4b3ace93d155cab82eb53c874aab666919b0b853f8babecf27095886fe3cd")(self);
    STLoad::get().loadResources();
}

void HK::GameManager::memInit(){
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
    HookManager::get().addHook("a7e4b3ace93d155cab82eb53c874aab666919b0b853f8babecf27095886fe3cd", base + 0x18C790, GameManager::reloadAllStep5);

}