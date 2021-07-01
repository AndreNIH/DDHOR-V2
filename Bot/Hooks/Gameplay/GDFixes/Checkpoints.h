#pragma once
#include "../../../../GDTypes/CheckpointObject.h"
#include "../../../../GDTypes/PlayerObject.h"

namespace HK{
    namespace PlayerObject{
        void __fastcall saveToCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint*);
		void __fastcall loadFromCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint*);
		void memInit();
    }
}