#include "Checkpoints.h"
#include <SimpleMemory/SimpleMemory.h>
#include <Hooks/HookManger.h>

typedef void(__thiscall* ret)(void*, void*);
void __fastcall HK::PlayerObject::saveToCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint* checkpoint){
	HookManager::get().getFunctionPtr<ret>("780c64bc81d66ceaf4878ec74a4311a7191e180d80844e9f10d0521d67c5e82a")(self,checkpoint);
	checkpoint->accYVelocity = self->yVelocityVec;
	checkpoint->xRotation = self->xRotation;
	checkpoint->yRotation = self->yRotation;
}

void __fastcall HK::PlayerObject::loadFromCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint* checkpoint)
{
	HookManager::get().getFunctionPtr<ret>("18785475ccfd16a0faca5489a2dda440b4cb7a3f7be508d3058192b50cae971e")(self,checkpoint);
	self->yVelocityVec = checkpoint->accYVelocity;
	self->xRotation = checkpoint->xRotation;
	self->yRotation = checkpoint->yRotation;
}

void HK::PlayerObject::memInit(){
	DWORD base = reinterpret_cast<DWORD>(GetModuleHandle(0));
	HookManager::get().addHook("780c64bc81d66ceaf4878ec74a4311a7191e180d80844e9f10d0521d67c5e82a", base + 0x1F9EE0, saveToCheckpoint); 
    HookManager::get().addHook("18785475ccfd16a0faca5489a2dda440b4cb7a3f7be508d3058192b50cae971e", base + 0x1FA080, loadFromCheckpoint); 
	sm::internal::write<char>(base + 0x20DC65, '\x24');
}