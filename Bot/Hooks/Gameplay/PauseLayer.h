#pragma once

namespace HK{
    namespace PauseLayer{
        bool __fastcall init(void* self);
        void __fastcall onResume(void* self, int edx, void* arg);
        void __fastcall onRestart(void* self, int edx, void* arg);
        void memInit();
    }
}