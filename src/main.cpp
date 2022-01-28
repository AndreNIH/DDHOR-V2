#include <iostream>
#include <gd.h>
#include <matdash/boilerplate.hpp>
#include "Hooks/Game/HKPlayLayer.h"
#include "Hooks/Menu/LevelInfoLayer.h"
#include "Bot/Engine.h"
#include <ErrorChecking/TextureVerifier.h>
#include <Loader/TextureLoader.h>
#include <fmt/format.h>
#include <GUI/GMDX/AlertBox.h>
#include <spdlog/spdlog.h>
void onTexturesLoaded(){
    const char* txMenuTest = "Texture::DS_Menu";
    Tester tester;
    bool success = tester.add(new TextureVerifier(txMenuTest,"D2B_BotMenu_001.png"))
                         .add(new TextureVerifier(txMenuTest,"D2B_LoadBtn_001.png"))
                         .add(new TextureVerifier(txMenuTest,"D2B_RecordBtn_001.png"))
                         .add(new TextureVerifier(txMenuTest,"D2B_StopPlayBtn_001.png"))
                         .add(new TextureVerifier(txMenuTest,"D2B_StopRecordBtn_001.png"))
                         .runAllTests();
    if(!success) {
        const float size = cocos2d::CCDirector::sharedDirector()->getWinSize().width * 0.75;
        const int passedTests = tester.getSuccessfulTests();
        const int totalTests = tester.getTotalTests();
        const std::string content =  "Only <cl>{} out of {}</c> DDHOR sprite verifications were succesful. "
                                     "Please restart your game.\nIf the error persists, <cr>re-install DDHOR</c>";
        
        gmdx::AlertBox alert;
        alert.setTitle("Failed to Verify Textures");
        alert.setSize(size);
        alert.setContent(fmt::format(content, passedTests, totalTests));
        alert.show();
    }else{

    }
};


void mod_main(HMODULE mod){
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    
    spdlog::set_level(spdlog::level::debug);
    gd::init();
    Hook::PlayLayer::memInit();
    Hook::LevelInfoLayer::memInit();
    
    TextureLoader::loadTextures(onTexturesLoaded);
    
}