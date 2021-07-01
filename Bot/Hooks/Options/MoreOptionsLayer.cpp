#include "MoreOptionsLayer.h"
#include <Hooks/HookManger.h>
 #include <Engine/Config.h>
 typedef int(__thiscall* addToggle_t)(void* _this, const char* display, const char* key, const char* extraInfo);
 addToggle_t addToggle = nullptr;
bool __fastcall HK::MoreOptionsLayer::init(void* self){
    auto pOriginal = HookManager::get().getFunctionPtr<bool(__thiscall*)(void*)>("e89b5240428d3d2c22ee7836d84ff1303051284abedf9ff7f55f8dc55218ee22");
    pOriginal(self);

    addToggle(
        self, 
        "Disable Delta Override", 
        DDHR_CONF_NO_DO, 
        "Similar to turning off Smooth Fix. Disabling Delta Override while trying to record or play a macro "
        "will result in inaccurate/inconsistent botting results."
        );

    addToggle(
        self,
        "Enable LEGAL mode",
        DDHR_CONF_SAFEMODE,
        "Prevents you from beating a level whilst playing a macro"
        );

    addToggle(
        self,
        "Disable Action-Sync",
        DDHR_CONF_NO_SYNC,
        "Action-sync is a technology that prevents desyncronization of the macro with the user's inputs by preventing"
        "the player from respawning from a practice checkpoint unless bot the bot's last recorded action and the player's input match. "
        "Toggling this option may lead to inaccurate macro recordings"
    );

    addToggle(
        self,
        "Instant Action-Sync respawn",
        DDHR_CONF_SYNC_NO_FADE,
        "Disables the fadeout animation from the Action-Sync layer. You will respawn as soon as your inputs align with the bot's"
    );
    return true;
}

void HK::MoreOptionsLayer::memInit(){
    uint32_t base = reinterpret_cast<uint32_t>(GetModuleHandle(0));
    HookManager::get().addHook("e89b5240428d3d2c22ee7836d84ff1303051284abedf9ff7f55f8dc55218ee22", base +0x1DE8F0, MoreOptionsLayer::init);
    addToggle = reinterpret_cast<addToggle_t>(base + 0x1DF6B0);
}