#pragma once
#include <unordered_map>
#include <string>
#include <utility>
#include <minhook/MinHook.h>
#include <strings_hash/strings_hash.h>

class HookManager {
private:
	//<id, function pointer>
	std::unordered_map<std::string, std::pair<void*,void*>>m_idToFunct;
public:
	static HookManager& get(){
		static HookManager instance;
		return instance;
	}

	MH_STATUS disableHook(const std::string& id);
	MH_STATUS enableHook(const std::string& id);
	
	bool addHook(const std::string& id, uint32_t target, void* detour);
	bool addHook(uint32_t hash, uint32_t target, void* detour){addHook(std::to_string(hash), target, detour);}

	void* getFunctionPtrRaw(const std::string& id);
	void* getFunctionPtrRaw(uint32_t hash){return getFunctionPtrRaw(std::to_string(hash));};
	
	template<typename T>
	inline T getFunctionPtr(const std::string& id) {
		static_assert(std::is_pointer<T>::value, "T must be a pointer");
		return reinterpret_cast<T>(getFunctionPtrRaw(id));
	}

	template<typename T>
	inline T getFunctionPtr(size_t hash){
		return getFunctionPtr(std::to_string(hash)); 
	}
	
	HookManager() { MH_Initialize(); }
	~HookManager() { MH_Uninitialize(); }
	HookManager(HookManager const&)    = delete;
	void operator=(HookManager const&) = delete;

};