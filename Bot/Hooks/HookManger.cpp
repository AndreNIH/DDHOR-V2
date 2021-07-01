#include "HookManger.h"
#include <minhook/MinHook.h>

bool HookManager::addHook(const std::string& id, uint32_t target, void* detour){
	void* pOriginal = nullptr;
	if (MH_CreateHook(reinterpret_cast<void*>(target), detour, &pOriginal) != MH_OK) 
		return false;
	m_idToFunct.insert({ id, {pOriginal, reinterpret_cast<void*>(target)} });
	return true;
}

void* HookManager::getFunctionPtrRaw(const std::string& id){
	auto it =m_idToFunct.find(id);
	return it != m_idToFunct.end() ? it->second.first : nullptr;
}


MH_STATUS HookManager::disableHook(const std::string& id){
	auto it = m_idToFunct.find(id);
	if(it == m_idToFunct.end()) return MH_ERROR_NOT_CREATED;
	else return MH_DisableHook(it->second.second);
}

MH_STATUS HookManager::enableHook(const std::string& id){
	auto it = m_idToFunct.find(id);
	if(it == m_idToFunct.end()) return MH_ERROR_NOT_CREATED;
	else return MH_EnableHook(it->second.second);
}